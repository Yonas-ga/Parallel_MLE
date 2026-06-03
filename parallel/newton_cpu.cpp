#include <vector>
#include <thread>
#include <cmath>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <numeric> 
using namespace std;


struct Data_struct {
    int outcome;
    vector<double> x;
};

double dot(vector<double>& a, vector<double>& b){
    double res = 0;
    for (size_t i = 0; i < a.size(); ++i){
        res += a[i]*b[i];
    }
    return res;
}

vector<double> solve(vector<double>& H, vector<double>& gradient, int d, int p){
    /// delta = solve (H * delta  = gradient);
    //      solve L x (L.T x delta) =: L x y = gradient
    // 1. Find L (lower matrix) s.t L x L.T = H
    //      H needs to be positive definite (could imporve by putting a plan B)
    // 2. Find y (vector) s.t. L x y = gradient
    // 3. Find delta (vector) s.t. (L.T x delta) = y

    // 1. Finding L
    int n = p*(d-1);
    vector<double> L(H.size(),0.0);
    // For all   j, L[j][j] = sqrt(H[j][j] - Sum_{0<k<n+1} L[j][k]*L[j][k])
    // For all i,j, L[i][j] = (H[i][j] - Sum_{0<k<j} L[i][k] L[j][k])/ L[j][j]

    for (size_t j = 0; j < n; ++j){
        double Sum_for_jj = 0.0;
        for (size_t k = 0; k < j; ++k){
            Sum_for_jj += L[j*n + k]*L[j*n + k];
        }

        if (H[j*n+j] - Sum_for_jj < 0){
            std::cout<< "Hessian NOT Negative"  << std::endl;
            return vector<double>{};
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
    vector<double> y(gradient.size(),0.0);
    // for all i, y[i] = (gradient[k] - Sum_{0<k<i-1} L[i][k] y[k])/L[i][i]
    for (size_t i = 0; i < n; ++i){
            double Sum_for_i = 0.0;
            for (size_t k = 0; k < i; ++k){
                Sum_for_i += L[i*n + k]*y[k];
            }
            y[i] = (gradient[i] - Sum_for_i)/L[i*n+i];
        }

    // 2. Finding delta
    vector<double> delta(gradient.size(),0.0);
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


int d = 5;   // number of families
int p = 3;   // number of features per family

// takes one family and adds its part to gradient and hessian
void add_one_family(const Data_struct& fam, const vector<double>& theta,
                    vector<double>& gradient, vector<double>& H, int p, int d, bool h) {
    int P = p * (d - 1);

    vector<double> score(d, 0.0);
    double denom = 1.0;
    for (int j = 0; j < d - 1; j++) {
        for (int k = 0; k < p; k++) {
            score[j] = score[j] + fam.x[k] * theta[j * p + k];
        }
        denom = denom + exp(score[j]);
    }

    // probabilities for every group for hessian
    vector<double> prob(d, 0.0);
    for (int j = 0; j < d - 1; j++) {
        prob[j] = exp(score[j]) / denom;
    }
    prob[d - 1] = 1.0 / denom;

    // gradient
    for (int j = 0; j < d - 1; j++) {
        double indicator = 0.0;
        if (j == fam.outcome) {
            indicator = 1.0;
        }
        for (int k = 0; k < p; k++) {
            gradient[j * p + k] += fam.x[k] * (indicator - prob[j]);
        }
    }
    
    if (h){
        // hessian
        for (int j = 0; j < d - 1; j++) {
            for (int l = 0; l < d - 1; l++) {
                double scal = 0.0;
                if (j == l) {
                    scal = prob[j] * (1.0 - prob[j]);
                } else {
                    scal = -prob[j] * prob[l];
                }
                for (int k1 = 0; k1 < p; k1++) {
                    for (int k2 = 0; k2 < p; k2++) {
                        int row = j * p + k1;
                        int col = l * p + k2;
                        H[row * P + col] += scal * fam.x[k1] * fam.x[k2];
                    }
                }
            }
        }
    }
}

// one core does all families
void compute_sequential(const vector<Data_struct>& data, const vector<double>& theta,
                        vector<double>& gradient, vector<double>& H, bool h) {
    int N = data.size();
    for (int i = 0; i < N; i++) {
        add_one_family(data[i], theta, gradient, H, p,d, h);
    }
}

// each worker does its part of families from start to end
void worker(const vector<Data_struct>& data, const vector<double>& theta,
            int start, int end, vector<double>& my_gradient, vector<double>& my_H, int p, int d,bool h) {
    for (int i = start; i < end; i++) {
        add_one_family(data[i], theta, my_gradient, my_H, p, d, h);
    }
}

// split families between T threads, then add up their gradients and hessians
void compute_parallel(const vector<Data_struct>& data, const vector<double>& theta, int T,
                      vector<double>& gradient, vector<double>& H, int p, int d, bool h) {
    int N = data.size();
    int P = p * (d - 1);

    // one gradient and one hessian for each thread, all start at zero
    vector<vector<double>> partial_grad(T);
    vector<vector<double>> partial_H(T);
    for (int t = 0; t < T; t++) {
        partial_grad[t].resize(P, 0.0);
        partial_H[t].resize(P * P, 0.0);
    }

    // start the threads
    vector<thread> threads;
    for (int t = 0; t < T; t++) {
        int start = t * N / T;
        int end = (t + 1) * N / T;
        threads.push_back(thread(worker, cref(data), cref(theta), start, end,
                                 ref(partial_grad[t]), ref(partial_H[t]), p , d, h));
    }

    // wait for all threads to finish
    for (int t = 0; t < T; t++) {
        threads[t].join();
    }

    // add all the partial gradients into one
    for (int t = 0; t < T; t++) {
        for (int k = 0; k < P; k++) {
            gradient[k] = gradient[k] + partial_grad[t][k];
        }
    }
    // add all the partial hessians into one
    for (int t = 0; t < T; t++) {
        for (int k = 0; k < P * P; k++) {
            H[k] = H[k] + partial_H[t][k];
        }
    }
}


pair<vector<double>, bool> gradient_ascent(vector<double>& theta, vector<Data_struct>& data, int T, int d, int p, bool h = true, bool verbose = true, double step=0.01,  int max_iter=1e6, double eps=1e-3){ //step and max_iter to be adjusted, possibly as an input of main.
    int N = data.size();
    for (int i=0; i<max_iter;i++){
        // Loss_Function_h tmp = Multinomial_logit(theta,data,d,p, h);
        vector<double> g(p*(d-1), 0.0);
        vector<double> H(p*(d-1)*p*(d-1), 0.0);
        compute_parallel(data, theta, T, g, H, p,d, h);

        if (verbose)  std::cout<<"||Gradient|| = "<< sqrt(dot(g,g)) << std::endl;

        
        if (sqrt(dot(g,g)) <eps) {
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
            return pair(theta,true);
        }
        if (!h){
            for (size_t j=0; j<theta.size();j++){
                theta[j] += step*g[j]/N;
            }
        }
        else{
            vector<double> delta(theta.size(), 0.0);
            delta = solve (H, g, d,p);
            if (delta.empty()){
                for (size_t j=0; j<theta.size();j++){
                    theta[j] += step*g[j]/N;
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

int main() {
    // int N = 1000000;   // a lot of families so the threads have work to do
    // int P = p * (d - 1);

    // // make random families
    // vector<Data_struct> data(N);
    // for (int i = 0; i < N; i++) {
    //     data[i].outcome = rand() % d;
    //     data[i].x.resize(p);
    //     for (int k = 0; k < p - 1; k++) {
    //         data[i].x[k] = (rand() % 2000 - 1000) / 1000.0;
    //     }
    //     data[i].x[p - 1] = 1.0;
    // }

    // vector<double> theta(P, 0.0);

    // // sequential, timed
    // vector<double> g_seq(P, 0.0);
    // vector<double> H_seq(P * P, 0.0);
    // auto t0 = chrono::steady_clock::now();
    // compute_sequential(data, theta, g_seq, H_seq);
    // auto t1 = chrono::steady_clock::now();
    // double seq_time = chrono::duration<double>(t1 - t0).count();
    // cout << "sequential: " << seq_time << " s" << endl;

    // // parallel for 1, 2, 3, 4 threads
    // for (int T = 1; T <= 4; T++) {
    //     vector<double> g_par(P, 0.0);
    //     vector<double> H_par(P * P, 0.0);

    //     auto a = chrono::steady_clock::now();
    //     compute_parallel(data, theta, T, g_par, H_par);
    //     auto b = chrono::steady_clock::now();
    //     double par_time = chrono::duration<double>(b - a).count();

    //     // biggest difference in the gradient
    //     double diff_g = 0.0;
    //     for (int k = 0; k < P; k++) {
    //         double diff = fabs(g_seq[k] - g_par[k]);
    //         if (diff > diff_g) {
    //             diff_g = diff;
    //         }
    //     }

    //     // biggest difference in the hessian
    //     double diff_H = 0.0;
    //     for (int k = 0; k < P * P; k++) {
    //         double diff = fabs(H_seq[k] - H_par[k]);
    //         if (diff > diff_H) {
    //             diff_H = diff;
    //         }
    //     }

    //     // how big are the hessian numbers themselves
    //     double biggest_H = 0.0;
    //     for (int k = 0; k < P * P; k++) {
    //         if (fabs(H_seq[k]) > biggest_H) {
    //             biggest_H = fabs(H_seq[k]);
    //         }
    //     }

    //     cout << T << " threads: " << par_time << " s";
    //     cout << " speedup: " << seq_time / par_time;

    //     if (diff_g < 1e-6 && diff_H < biggest_H * 1e-8) {
    //         cout << " match: YES" << endl;
    //     } else {
    //         cout << " match: NO" << endl;
    //     }
    // }
    // return 0;

    // After the results vector is populated:
    std::ofstream csv("Parralel results.csv");

        csv << "N,T,p,d,"
        << "runtime_h_us,runtime_g_us,"
        << "mean_error_h,max_error_h,"
        << "mean_error_g,max_error_g, converged_h, converged_g\n";

    int p = 5;
    for (int T = 2; T<10; T++){
        for (int d = 2; d<5; d++) {
            for (int n0 = 1; n0 < 4; n0++) {
                cout<< "n = " << n0*5000 << " , p*(d-1) = " << p*(d-1) << " , T = " << T << endl;
                vector<double> true_theta ((d-1)*p, 0.0);
                vector<double> x (p, 0.0);
                vector<double> theta_mle ((d-1)*p, 0.0);
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

                vector<double> theta_mle_h(p*(d-1), 0.0);
                vector<double> theta_mle_g(p*(d-1), 0.0);

                auto start_h = std::chrono::high_resolution_clock::now();
                auto tmp_h = gradient_ascent(theta_mle_h, data_mle, T, d, p, true, false); 
                auto end_h = std::chrono::high_resolution_clock::now();
                
                vector<double> result_mle_h = tmp_h.first;
                auto runtime_h = std::chrono::duration_cast<std::chrono::microseconds>(end_h - start_h);
                runtime_h = runtime_h;
                bool cvg_h = tmp_h.second;

                auto start_g = std::chrono::high_resolution_clock::now();
                auto tmp_g = gradient_ascent(theta_mle_g, data_mle, T, d, p, false, false);
                auto end_g = std::chrono::high_resolution_clock::now();
                
                vector<double> result_mle_g = tmp_g.first;
                auto runtime_g = std::chrono::duration_cast<std::chrono::microseconds>(end_g - start_g);
                runtime_g = runtime_g;
                bool cvg_g = tmp_g.second;

                vector<double> errors_h(p*(d-1), 0.0);
                vector<double> errors_g(p*(d-1), 0.0);

                for (int i = 0; i < p*(d-1); i++) {
                    errors_h[i] = std::abs(result_mle_h[i] - true_theta[i]); 
                    errors_g[i] = std::abs(result_mle_g[i] - true_theta[i]); 
                }

                // Summarize per-parameter errors into mean and max
                double sum_h = 0.0, max_h = 0.0;
                double sum_g = 0.0, max_g = 0.0;

                for (double e : errors_h) { sum_h += e; max_h = std::max(max_h, e); }
                for (double e : errors_g) { sum_g += e; max_g = std::max(max_g, e); }

                int n_params = p * (d - 1);
                double mean_h = errors_h.empty() ? 0.0 : sum_h / n_params;
                double mean_g = errors_g.empty() ? 0.0 : sum_g / n_params;

                csv << 5000*n0         << ","
                    << T         << ","
                    << p         << ","
                    << d         << ","
                    << runtime_h.count() << ","
                    << runtime_g.count() << ","
                    << mean_h      << ","
                    << max_h       << ","
                    << mean_g      << ","
                    << max_g       << ","
                    << cvg_h      << ","
                    << cvg_g      << "\n";
                csv.flush(); // ← add this
            }
        }
    }

    csv.close();
    std::cout << "Results written to results.csv" << std::endl;
}