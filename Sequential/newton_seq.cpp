#include <vector>
#include <cmath>
#include <iostream>
#include <chrono>
#include <fstream>
#include <numeric>   // for std::accumulate
#include "../data.hpp"


struct SimulationResult {
    int N;
    int p;
    int d;

    bool cvg_h;
    bool cvg_g;

    Vector errors_h;
    Vector errors_g;
    std::chrono::microseconds runtime_h;
    std::chrono::microseconds runtime_g;
};


// Helper Functions


Vector solve(Vector& H, Vector& gradient, int d, int p){
    /// delta = solve (H * delta  = gradient);
    //      solve L x (L.T x delta) =: L x y = gradient
    // 1. Find L (lower matrix) s.t L x L.T = H
    //      H needs to be positive definite (could imporve by putting a plan B)
    // 2. Find y (vector) s.t. L x y = gradient
    // 3. Find delta (vector) s.t. (L.T x delta) = y

    // 1. Finding L
    int n = p*(d-1);
    Vector L(H.size(),0.0);
    // For all   j, L[j][j] = sqrt(H[j][j] - Sum_{0<k<n+1} L[j][k]*L[j][k])
    // For all i,j, L[i][j] = (H[i][j] - Sum_{0<k<j} L[i][k] L[j][k])/ L[j][j]

    for (size_t j = 0; j < n; ++j){
        double Sum_for_jj = 0.0;
        for (size_t k = 0; k < j; ++k){
            Sum_for_jj += L[j*n + k]*L[j*n + k];
        }

        if (H[j*n+j] - Sum_for_jj < 0){
            std::cout<< "Hessian NOT Negative"  << std::endl;
            return Vector{};
        }
        L[j*n + j] = sqrt(H[j*n+j] - Sum_for_jj);

        for (size_t i = j+1; i < n; ++i){
            double Sum_for_ij = 0.0;
            for (size_t k = 0; k < j; ++k){
                Sum_for_ij += L[i*n + k]*L[j*n + k];
            }
            L[i*n + j] += (H[i*n + j] - Sum_for_ij)/L[j*n+j];
        }
    }

    // 2. Finding y 
    Vector y(gradient.size(),0.0);
    // for all i, y[i] = (gradient[k] - Sum_{0<k<i-1} L[i][k] y[k])/L[i][i]
    for (size_t i = 0; i < n; ++i){
            double Sum_for_i = 0.0;
            for (size_t k = 0; k < i; ++k){
                Sum_for_i += L[i*n + k]*y[k];
            }
            y[i] = (gradient[i] - Sum_for_i)/L[i*n+i];
        }

    // 2. Finding delta
    Vector delta(gradient.size(),0.0);
    // for all i, delta[i] = (y[k] - Sum_{0<k<i-1} L[k][i] delta[k])/L[i][i]
    for (int i = n-1; i >= 0; --i){
        double Sum_for_i = 0.0;
        for (size_t k = i+1; k < n; ++k){
            Sum_for_i += L[k*n + i] * delta[k];
        }
        delta[i] = (y[i] - Sum_for_i)/L[i*n+i];
    }

    return delta;
}


// MLE functions
Loss_Function_h Multinomial_logit(Vector& theta, std::vector<Data_struct>& data, int d, int p, bool h){  //Computes de loss function, Multinomial_logit is the one used in the reference paper.
    // Multinomial Logit
    // Log Likelihood = Sum_{observtion} Sum_{k} Indicator{Output=k} [X_k \theta_k - log(Sum_{j} exp(X_j \theta_j))

    int N = data.size();
    double ll = 0;
    Vector gradient(theta.size(), 0.0);
    Vector H(theta.size()*theta.size(), 0.0);

    for (Data_struct& data_point : data){

        std::vector<double> lcom(d, 0.0);
        std::vector<double> P(d, 0.0);
        double denom = 0;

        for (size_t j = 0; j < d-1; ++j){
            for (size_t k = 0; k < p; ++k){
                lcom[j] += data_point.x[k] *  theta[p*j + k];
            }
            denom += exp(lcom[j]);
        }

        lcom[d-1] = 0.0;
        denom += 1.0;
        

        for (size_t j = 0; j < d; ++j){
            P[j] = exp(lcom[j])/denom;
        }
        

        /// Log Loss
        ll += (lcom[data_point.outcome] - log(denom))/N;


        /// Gradient
        for (size_t j = 0; j < d-1; ++j){
            double ind = 0;
            if (j ==data_point.outcome){ 
                ind = 1;
            }
            for(size_t k = 0; k<p; k++){
                gradient[j*p + k] += (data_point.x[k] * (ind - P[j]))/N;
            }
        }

        /// Hessian
        if (h){
            for (size_t j = 0; j < d-1; ++j){
                for (size_t l = 0; l < d-1; ++l){
                    double scal = 0.0;
                    if (j ==l){ 
                        scal = P[j]*(1.0-P[j]);
                    }
                    else{
                        scal = -P[j]*P[l];
                    }
                    for(size_t k1 = 0; k1<p; k1++){
                        for(size_t k2 = 0; k2<p; k2++){
                            H[(j*p + k1)*(p*(d-1)) + l*p + k2] += scal * data_point.x[k1] * data_point.x[k2]/N;
                        }
                    }
                }
            }
        }
    }

    Loss_Function_h res;
    if (h){
        res.value = ll;
        res.gradient = gradient;
        res.H = H;
    }
    else {
            res.value = ll;
        res.gradient = gradient;
    }
    return res;
} 

std::pair<Vector, bool> gradient_ascent(Vector& theta, Data_vect& data, int d, int p, bool h = true, bool verbose = true, double step=0.07,  int max_iter=1e6, double eps=1e-3){ //step and max_iter to be adjusted, possibly as an input of main.
    int N = data.size();
    for (int i=0; i<max_iter;i++){
        Loss_Function_h tmp = Multinomial_logit(theta,data,d,p, h);
        if (verbose)  std::cout<<"||Gradient|| = "<< sqrt(dot(tmp.gradient,tmp.gradient)) << std::endl;

        
        if (sqrt(dot(tmp.gradient,tmp.gradient)) <eps) {
            std::cout<<"eps = "<< eps << " reached!"<< std::endl;
            // std::cout<< "------------------------------------------"  << std::endl;
            // int j = 0;
            //     for (double v : tmp.H) {
            //         if (j==p*(d-1)){
            //             std::cout << std::endl;
            //             j=0;
            //         }
            //         std::cout << v << " ";
            //         j ++;
            //     }
            //     std::cout << std::endl;
            // std::cout<< "------------------------------------------" << std::endl;
            return std::pair(theta,true);
        }
        if (!h){
            for (size_t j=0; j<theta.size();j++){
                theta[j] += step*tmp.gradient[j];
            }
        }
        else{
            Vector delta(theta.size(), 0.0);
            delta = solve (tmp.H, tmp.gradient, d,p);
            if (delta.empty()){
                for (size_t j=0; j<theta.size();j++){
                    theta[j] += step*tmp.gradient[j];
                }
            }
            else {
                for (size_t j=0; j<theta.size();j++){
                    theta[j] += delta[j];
                }
            }
            
        }
    }
    std::cout<<"max_iter = "<< max_iter << " reached!"<< std::endl;
    return std::pair(theta,false);
}


int main(){
    srand(42);
    // int N; // Number of observations
    // int d = 5; // Number of possible outcomes including base
    // int p = 3; // Number of features


    // Testing Khaled's sequential MLE
    // Vector theta_mle ((d-1)*p, 0.0);
    // True theta: beta_1=[1.0,-1.0], beta_2=[-1.0,1.0], beta_3=[0,0] (baseline)
    // k=2 features, d=3 alternatives
    // std::vector<Data_struct> data_paper = read_data("Data/FAM1968_parsed_full.csv");
    // std::vector<Data_struct> data_mle;
    // for (int i = 0; i < 100; i++) {
    //     double x1 = (rand() % 2000 - 1000) / 1000.0;
    //     double x2 = (rand() % 2000 - 1000) / 1000.0;
    //     double x3 = (rand() % 2000 - 1000) / 1000.0;
    //     double x4 = (rand() % 2000 - 1000) / 1000.0;
    //     double x5 = 1.0;

    //     int outcome;

    //     double s0 = 2*x1 - x2;
    //     double s1 = -x1 + 2*x2;
    //     double s2 = x3;
    //     double s3 = -x4;

    //     if (s0 >= s1 && s0 >= s2 && s0 >= s3 && s0 >= 0){
    //         outcome = 0;
    //     } else if (s1 >= s2 && s1 >= s3 && s1 >= 0){
    //         outcome = 1;
    //     } else if (s2 >= s3 && s2 >= 0){
    //         outcome = 2;
    //     } else if (s3 >= 0){
    //         outcome = 3;
    //     } else{
    //         outcome = 4; 
    //     }
    //     //data_mle.push_back({outcome, {x1,x2,x3,x4,x5}});
    // }

    // After the results vector is populated:
    std::ofstream csv("results.csv");

    // Header
    csv << "N,p,d,"
        << "runtime_h_us,runtime_g_us,"
        << "mean_error_h,max_error_h,"
        << "mean_error_g,max_error_g, converged_h, converged_g\n";

    int p = 5;
        for (int d = 20; d<40; d++) {
            for (int n0 = 1; n0 < 2; n0++) {
                Vector true_theta ((d-1)*p, 0.0);
                Vector x (p, 0.0);
                Vector theta_mle ((d-1)*p, 0.0);
                std::vector<Data_struct> data_mle;

                for (int i = 0; i < p*(d-1); i++) {
                    true_theta[i] = (rand() % 2000 - 1000) / 1000.0;  //// Try running less nice true_theta
                }

                for (int i = 0; i < 5000*n0; i++) {
                    for (int k = 0; k<p-1; k++) {
                        x[k] = (rand() % 2000 - 1000) / 1000.0;
                    }
                    x[p-1] = 1.0;

                    std::vector<double> score(d, 0.0);
                    double denom = 1.0; 

                    for (int j = 0; j < d-1; j++) {
                        for (int k = 0; k < p; k++) {
                            score[j] += x[k] * true_theta[j*p + k];
                        }
                        denom += exp(score[j]);
                    }

                    std::vector<double> prob(d, 0.0);
                    double cumulative = 0.0;

                    for (int j = 0; j < d-1; j++) {
                        prob[j] = exp(score[j]) / denom;
                    }
                    prob[d-1] = 1.0 / denom;

                    double u = rand() / (double)RAND_MAX;

                    int outcome = d-1;
                    cumulative = 0.0;

                    for (int j = 0; j < d; j++) {
                        cumulative += prob[j];
                        if (u < cumulative) {
                            outcome = j;
                            break;
                        }
                    }
                    data_mle.push_back({outcome, x});
                }
            
                // Pushing results out
                SimulationResult res;
                res.p = p;
                res.d = d;
                res.N = 5000*n0;

                Vector theta_mle_h(p*(d-1), 0.0);
                Vector theta_mle_g(p*(d-1), 0.0);

                auto start_h = std::chrono::high_resolution_clock::now();
                auto tmp_h = gradient_ascent(theta_mle_h, data_mle, d, p, true, false); 
                auto end_h = std::chrono::high_resolution_clock::now();
                
                Vector result_mle_h = tmp_h.first;
                auto runtime_h = std::chrono::duration_cast<std::chrono::microseconds>(end_h - start_h);
                res.runtime_h = runtime_h;
                res.cvg_h = tmp_h.second;

                auto start_g = std::chrono::high_resolution_clock::now();
                auto tmp_g = gradient_ascent(theta_mle_g, data_mle, d, p, false, false);
                auto end_g = std::chrono::high_resolution_clock::now();
                
                Vector result_mle_g = tmp_g.first;
                auto runtime_g = std::chrono::duration_cast<std::chrono::microseconds>(end_g - start_g);
                res.runtime_g = runtime_g;
                res.cvg_g = tmp_g.second;

                Vector errors_h(p*(d-1), 0.0);
                Vector errors_g(p*(d-1), 0.0);

                for (int i = 0; i < p*(d-1); i++) {
                    errors_h[i] = std::abs(result_mle_h[i] - true_theta[i]); 
                    errors_g[i] = std::abs(result_mle_g[i] - true_theta[i]); 
                }
                res.errors_h = errors_h;
                res.errors_g = errors_g;

                // Summarize per-parameter errors into mean and max
                double sum_h = 0.0, max_h = 0.0;
                double sum_g = 0.0, max_g = 0.0;

                for (double e : res.errors_h) { sum_h += e; max_h = std::max(max_h, e); }
                for (double e : res.errors_g) { sum_g += e; max_g = std::max(max_g, e); }

                int n_params = res.p * (res.d - 1);
                double mean_h = res.errors_h.empty() ? 0.0 : sum_h / n_params;
                double mean_g = res.errors_g.empty() ? 0.0 : sum_g / n_params;

                csv << res.N         << ","
                    << res.p         << ","
                    << res.d         << ","
                    << res.runtime_h.count() << ","
                    << res.runtime_g.count() << ","
                    << mean_h      << ","
                    << max_h       << ","
                    << mean_g      << ","
                    << max_g       << ","
                    << res.cvg_h      << ","
                    << res.cvg_g      << "\n";
                csv.flush(); // ← add this
            }
        }


    csv.close();
    std::cout << "Results written to results.csv" << std::endl;
} // Pipeline

