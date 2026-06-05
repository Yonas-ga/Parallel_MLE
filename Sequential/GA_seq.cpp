#include <vector>
#include <cmath>
#include <iostream>
#include <chrono>
#include <fstream>
#include <numeric>   // for std::accumulate
#include "../data.hpp"

double dot(Vector& a, Vector& b){
    double res = 0;
    for (size_t i = 0; i < a.size(); ++i){
        res += a[i]*b[i];
    }
    return res;
};

// MLE functions
Loss_Function_h Multinomial_logit_GA(Vector& theta, std::vector<Data_struct>& data, int d, int p){  //Computes de loss function, Multinomial_logit is the one used in the reference paper.
    // Multinomial Logit
    // Log Likelihood = Sum_{observtion} Sum_{k} Indicator{Output=k} [X_k \theta_k - log(Sum_{j} exp(X_j \theta_j))

    int N = data.size();
    double ll = 0;
    Vector gradient(theta.size(), 0.0);

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
    }

    Loss_Function_h res;
    res.value = ll;
    res.gradient = gradient;
    return res;
} 

std::pair<Vector, bool> gradient_ascent(Vector& theta, Data_vect& data, int d, int p, bool verbose, double step,  int max_iter, double eps){ //step and max_iter to be adjusted, possibly as an input of main.
    int N = data.size();
    for (int i=0; i<max_iter;i++){
        Loss_Function_h tmp = Multinomial_logit_GA(theta,data,d,p);
        if (verbose)  std::cout<<"||Gradient_SEQ|| = "<< sqrt(dot(tmp.gradient,tmp.gradient)) << std::endl;

        
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
        for (size_t j=0; j<theta.size();j++){
            theta[j] += step*tmp.gradient[j];
        }
    }
    std::cout<<"max_iter = "<< max_iter << " reached!"<< std::endl;
    return std::pair(theta,false);
}