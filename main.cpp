// This file will be used as the main pipeline, calling GA and Newton, both sequential and parallel.

#include <vector>
#include <cmath>
#include <iostream>
#include <chrono>
#include <fstream>
#include <numeric>   // for std::accumulate
#include "data.hpp"

void compare_seq(){
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
                auto tmp_h = Newton_ascent(theta_mle_h, data_mle, d, p, false); 
                auto end_h = std::chrono::high_resolution_clock::now();
                
                Vector result_mle_h = tmp_h.first;
                auto runtime_h = std::chrono::duration_cast<std::chrono::microseconds>(end_h - start_h);
                res.runtime_h = runtime_h;
                res.cvg_h = tmp_h.second;

                auto start_g = std::chrono::high_resolution_clock::now();
                auto tmp_g = gradient_ascent(theta_mle_g, data_mle, d, p, false);
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
}




int main(){
    compare_seq();
    return 0;
} //Main pipeline