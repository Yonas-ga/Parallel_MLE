#include <vector>
#include <cmath>
#include <iostream>
#include <chrono>
#include <fstream>
#include <numeric>   // for std::accumulate
#include "../data.hpp"

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
Loss_Function_h Multinomial_logit_Newton(Vector& theta, std::vector<Data_struct>& data, int d, int p){  //Computes de loss function, Multinomial_logit is the one used in the reference paper.
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

    Loss_Function_h res;
    res.value = ll;
    res.gradient = gradient;
    res.H = H;

    return res;
} 

std::pair<Vector, bool> Newton_ascent(Vector& theta, Data_vect& data, int d, int p, bool verbose, double step,  int max_iter, double eps){ //step and max_iter to be adjusted, possibly as an input of main.
    int N = data.size();
    for (int i=0; i<max_iter;i++){
        Loss_Function_h tmp = Multinomial_logit_Newton(theta,data,d,p);
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
        Vector delta(theta.size(), 0.0);
        delta = solve(tmp.H, tmp.gradient, d,p);
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
    std::cout<<"max_iter = "<< max_iter << " reached!"<< std::endl;
    return std::pair(theta,false);
}