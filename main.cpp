// This file will be used as the main pipeline, calling GA and Newton, both sequential and parallel.

#include <vector>
#include <cmath>
#include <iostream>
#include <chrono>
#include <fstream>
#include <numeric>   // for std::accumulate
#include "data.hpp"

std::pair<Data_vect,Vector> create_data(int N, int p, int d){
    Vector true_theta((d - 1) * p, 0.0);
    Vector x(p, 0.0);
    Data_vect data_mle;
    for (int i = 0; i < p*(d-1); i++) {
        true_theta[i] = (rand() % 2000 - 1000) / 1000.0; 
    }

    for (int i = 0; i < N; i++) {
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
    std::pair<Data_vect,Vector> res;
    res.first = data_mle;
    res.second = true_theta;
    return res;
}

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
        << "mean_error_g,max_error_g,"
        << "mean_error_h_g, converged_h, converged_g\n";

    int p = 5;
        for (int d = 2; d<3; d++) { /// theta_0 needs to be fixed regardless of sample size
            int N_max = 30 * 5000;
            auto res = create_data(N_max, p, d);
            Data_vect data_full = res.first;
            Vector true_theta = res.second;
            for (int n0 = 1; n0 < 31; n0++) {
                int N = 5000*n0;

                // Slice: first N observations of the full dataset
                Data_vect data_mle(data_full.begin(), data_full.begin() + N);                

                Vector theta_mle_h(p*(d-1), 0.0);
                Vector theta_mle_g(p*(d-1), 0.0);

                auto start_h = std::chrono::high_resolution_clock::now();
                auto tmp_h = Newton_ascent(theta_mle_h, data_mle, d, p, false); 
                auto end_h = std::chrono::high_resolution_clock::now();
                
                Vector result_mle_h = tmp_h.first;
                auto runtime_h = std::chrono::duration_cast<std::chrono::microseconds>(end_h - start_h);
                bool cvg_h = tmp_h.second;

                auto start_g = std::chrono::high_resolution_clock::now();
                auto tmp_g = gradient_ascent(theta_mle_g, data_mle, d, p, false);
                auto end_g = std::chrono::high_resolution_clock::now();
                
                Vector result_mle_g = tmp_g.first;
                auto runtime_g = std::chrono::duration_cast<std::chrono::microseconds>(end_g - start_g);
                bool cvg_g = tmp_g.second;

                Vector errors_h(p*(d-1), 0.0);
                Vector errors_g(p*(d-1), 0.0);
                Vector errors_h_g(p*(d-1), 0.0);

                for (int i = 0; i < p*(d-1); i++) {
                    errors_h[i] = std::abs(result_mle_h[i] - true_theta[i]); 
                    errors_g[i] = std::abs(result_mle_g[i] - true_theta[i]); 
                    errors_h_g[i] = std::abs(result_mle_g[i] - result_mle_h[i]); 
                }

                // Summarize per-parameter errors into mean and max
                double sum_h = 0.0, max_h = 0.0;
                double sum_g = 0.0, max_g = 0.0;
                double sum_h_g = 0.0;

                for (double e : errors_h) { sum_h += e; max_h = std::max(max_h, e); }
                for (double e : errors_g) { sum_g += e; max_g = std::max(max_g, e); }
                for (double e : errors_h_g) { sum_h_g += e; }

                int n_params = p * (d - 1);
                double mean_h = errors_h.empty() ? 0.0 : sum_h / n_params;
                double mean_g = errors_g.empty() ? 0.0 : sum_g / n_params;
                double mean_h_g = errors_g.empty() && errors_h.empty() ? 0.0 : sum_h_g / n_params;

                csv << N         << ","
                    << p         << ","
                    << d         << ","
                    << runtime_h.count() << ","
                    << runtime_g.count() << ","
                    << mean_h      << ","
                    << max_h       << ","
                    << mean_g      << ","
                    << max_g       << ","
                    << mean_h_g    << ","
                    << cvg_h       << ","
                    << cvg_g       << "\n";
                csv.flush(); // ← add this
            }
        }
    csv.close();
    std::cout << "Results written to results.csv" << std::endl;
}


void compare_parallel() {
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
        << "mean_error_g,max_error_g,"
        << "mean_error_h_g, converged_h, converged_g\n";

    int p = 5;
    for (int d = 2; d<3; d++) {
        int N_max = 30 * 5000;
        auto res = create_data(N_max, p, d);
        Data_vect data_full = res.first;
        Vector true_theta = res.second;
        for (int T = 2; T<10; T++){
            for (int n0 = 1; n0 < 31; n0++) {
                int N = 5000*n0;

                // Slice: first N observations of the full dataset
                Data_vect data_mle(data_full.begin(), data_full.begin() + N);  

                Vector theta_mle_h(p*(d-1), 0.0);
                Vector theta_mle_g(p*(d-1), 0.0);

                auto start_h = std::chrono::high_resolution_clock::now();
                auto tmp_h = Newton_ascent_cpu_lazy(theta_mle_h, data_mle, T, d, p, false); 
                auto end_h = std::chrono::high_resolution_clock::now();
                
                Vector result_mle_h = tmp_h.first;
                auto runtime_h = std::chrono::duration_cast<std::chrono::microseconds>(end_h - start_h);
                bool cvg_h = tmp_h.second;

                auto start_g = std::chrono::high_resolution_clock::now();
                auto tmp_g = gradient_ascent_cpu_lazy(theta_mle_g, data_mle, T, d, p, false);

                auto end_g = std::chrono::high_resolution_clock::now();
                
                Vector result_mle_g = tmp_g.first;
                auto runtime_g = std::chrono::duration_cast<std::chrono::microseconds>(end_g - start_g);
                bool cvg_g = tmp_g.second;

                Vector errors_h(p*(d-1), 0.0);
                Vector errors_g(p*(d-1), 0.0);
                Vector errors_h_g(p*(d-1), 0.0);
                

                for (int i = 0; i < p*(d-1); i++) {
                    errors_h[i] = std::abs(result_mle_h[i] - true_theta[i]); 
                    errors_g[i] = std::abs(result_mle_g[i] - true_theta[i]); 
                    errors_h_g[i] = std::abs(result_mle_h[i] - result_mle_g[i]); 
                }

                // Summarize per-parameter errors into mean and max
                double sum_h = 0.0, max_h = 0.0;
                double sum_g = 0.0, max_g = 0.0;
                double sum_h_g = 0.0;

                for (double e : errors_h) { sum_h += e; max_h = std::max(max_h, e); }
                for (double e : errors_g) { sum_g += e; max_g = std::max(max_g, e); }
                for (double e : errors_h_g) { sum_h_g += e; }

                int n_params = p * (d - 1);
                double mean_h = errors_h.empty() ? 0.0 : sum_h / n_params;
                double mean_g = errors_g.empty() ? 0.0 : sum_g / n_params;
                double mean_h_g = errors_h.empty()&& errors_g.empty() ? 0.0 : sum_h_g / n_params;

                csv << N         << ","
                    << T         << ","
                    << p         << ","
                    << d         << ","
                    << runtime_h.count() << ","
                    << runtime_g.count() << ","
                    << mean_h      << ","
                    << max_h       << ","
                    << mean_g      << ","
                    << max_g       << ","
                    << mean_h_g    << ","
                    << cvg_h       << ","
                    << cvg_g       << "\n";
                csv.flush(); // ← add this
            }
        }
    }
    csv.close();
    std::cout << "Results written to results.csv" << std::endl;
}

void test_all_gradient() {
    srand(42);

    int N = 5000;
    int p = 8;
    int d = 7;

    auto res = create_data(N, p, d);

    Data_vect data_mle = res.first;
    Vector true_theta = res.second;


    Vector theta_seq((d - 1) * p, 0.0);
    Vector theta_cpu((d - 1) * p, 0.0);
    Vector theta_cpu_cv((d - 1) * p, 0.0);
    Vector theta_gpu((d - 1) * p, 0.0);
    int number_threads = 8;
    auto start_cpu_cv = std::chrono::high_resolution_clock::now();
    auto res_cpu_cv = gradient_ascent_cpu_cv(theta_cpu_cv, data_mle, number_threads, d, p);
    auto end_cpu_cv = std::chrono::high_resolution_clock::now();
    auto start_cpu = std::chrono::high_resolution_clock::now();
    auto res_cpu = gradient_ascent_cpu_lazy(theta_cpu, data_mle, number_threads, d, p);
    auto end_cpu = std::chrono::high_resolution_clock::now();
    auto start_gpu = std::chrono::high_resolution_clock::now();
    auto res_gpu = gradient_ascent_gpu(theta_gpu, data_mle, d, p);
    auto end_gpu = std::chrono::high_resolution_clock::now();
    auto start_seq = std::chrono::high_resolution_clock::now();
    auto res_seq = gradient_ascent(theta_seq,data_mle,d,p);
    auto end_seq = std::chrono::high_resolution_clock::now();
    
    double time_seq = std::chrono::duration<double>(end_seq - start_seq).count();
    double time_cpu = std::chrono::duration<double>(end_cpu - start_cpu).count();
    double time_cpu_cv = std::chrono::duration<double>(end_cpu_cv - start_cpu_cv).count();
    double time_gpu = std::chrono::duration<double>(end_gpu - start_gpu).count();
    std::cout << "\nExecution times:\n";
    std::cout << "Sequential : " << time_seq << " s\n";
    std::cout << "CPU Lazy   : " << time_cpu << " s\n";
    std::cout << "CPU CV     : " << time_cpu_cv << " s\n";
    std::cout << "GPU        : " << time_gpu << " s\n";

    Vector result_seq = res_seq.first;
    Vector result_cpu = res_cpu.first;
    Vector results_cpu_cv = res_cpu_cv.first;
    Vector result_gpu = res_gpu.first;
    std::cout << "\nSEQ vs CPU vs CPU_CV vs GPU result comparison:\n";

    for (int i = 0; i < (d - 1) * p; i++) {
        std::cout << "theta[" << i << "] " <<"Seq = "<<result_seq[i]<< " CPU = " << result_cpu[i] << " CPU_cv = "<<results_cpu_cv[i] << " GPU = " << result_gpu[i] << std::endl;
    }
    std::cout << "Seq converged = " << res_seq.second << std::endl;
    std::cout << "CPU converged = " << res_cpu.second << std::endl;
    std::cout << "CPU_cv converged = " << res_cpu_cv.second << std::endl;
    std::cout << "GPU converged = " << res_gpu.second << std::endl;
}

void test_all_newton(){
    srand(42);

    int N = 100000;
    int p = 10;
    int d = 9;

    Vector true_theta((d - 1) * p, 0.0);
    Vector x(p, 0.0);
    Data_vect data_mle;
    for (int i = 0; i < p*(d-1); i++) {
        true_theta[i] = (rand() % 2000 - 1000) / 1000.0;  //// Try running less nice true_theta
    }

    for (int i = 0; i < N; i++) {
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
    Vector theta_seq((d - 1) * p, 0.0);
    Vector theta_cpu((d - 1) * p, 0.0);
    Vector theta_cpu_cv((d - 1) * p, 0.0);
    Vector theta_gpu((d - 1) * p, 0.0);
    int number_threads = 15;
    auto start_cpu_cv = std::chrono::high_resolution_clock::now();
    auto res_cpu_cv = Newton_ascent_cpu_cv(theta_cpu_cv, data_mle, number_threads, d, p);
    auto end_cpu_cv = std::chrono::high_resolution_clock::now();
    auto start_cpu = std::chrono::high_resolution_clock::now();
    auto res_cpu = Newton_ascent_cpu_lazy(theta_cpu, data_mle, number_threads, d, p);
    auto end_cpu = std::chrono::high_resolution_clock::now();
    auto start_gpu = std::chrono::high_resolution_clock::now();
    auto res_gpu = Newton_ascent_gpu(theta_gpu, data_mle, d, p);
    auto end_gpu = std::chrono::high_resolution_clock::now();
    auto start_seq = std::chrono::high_resolution_clock::now();
    auto res_seq = Newton_ascent(theta_seq,data_mle,d,p);
    auto end_seq = std::chrono::high_resolution_clock::now();
    
    double time_seq = std::chrono::duration<double>(end_seq - start_seq).count();
    double time_cpu = std::chrono::duration<double>(end_cpu - start_cpu).count();
    double time_cpu_cv = std::chrono::duration<double>(end_cpu_cv - start_cpu_cv).count();
    double time_gpu = std::chrono::duration<double>(end_gpu - start_gpu).count();
    std::cout << "\nExecution times:\n";
    std::cout << "Sequential : " << time_seq << " s\n";
    std::cout << "CPU Lazy   : " << time_cpu << " s\n";
    std::cout << "CPU CV     : " << time_cpu_cv << " s\n";
    std::cout << "GPU        : " << time_gpu << " s\n";

    Vector result_seq = res_seq.first;
    Vector result_cpu = res_cpu.first;
    Vector results_cpu_cv = res_cpu_cv.first;
    Vector result_gpu = res_gpu.first;
    std::cout << "\nSEQ vs CPU vs CPU_CV vs GPU result comparison:\n";

    for (int i = 0; i < (d - 1) * p; i++) {
        std::cout << "theta[" << i << "] " <<"Seq = "<<result_seq[i]<< " CPU = " << result_cpu[i] << " CPU_cv = "<<results_cpu_cv[i] << " GPU = " << result_gpu[i] << std::endl;
    }
    std::cout << "Seq converged = " << res_seq.second << std::endl;
    std::cout << "CPU converged = " << res_cpu.second << std::endl;
    std::cout << "CPU_cv converged = " << res_cpu_cv.second << std::endl;
    std::cout << "GPU converged = " << res_gpu.second << std::endl;
}

void tune_hyper_GPU(){
    double least_num = 1000;
    std::pair<int,int> least= {0,0};
    int N = 5000;
    int p = 8;
    int d = 7;
    auto res = create_data(N, p, d);

    Data_vect data_mle = res.first;
    Vector true_theta = res.second;
    int box_sizes[13]= {1,2,3,4,8,12,16,32,64,128,256,512,1024};
    int block_sizes[11] = {1,2,3,4,8,16,32,64,128,256,512};
    for (int box_size : box_sizes){
        for (int block_size : block_sizes){
            Vector theta_gpu((d - 1) * p, 0.0);
            auto start_gpu = std::chrono::high_resolution_clock::now();
            auto res_gpu = gradient_ascent_gpu(theta_gpu, data_mle, d, p,false, box_size, block_size);
            auto end_gpu = std::chrono::high_resolution_clock::now();
            double time_gpu = std::chrono::duration<double>(end_gpu - start_gpu).count();
            if(time_gpu < least_num){
                least_num = time_gpu;
                least.first = box_size;
                least.second=block_size;
            }
            std::cout << "GPU  : " << time_gpu << " s   for box_size = "<< box_size << " and block_size = "<<block_size <<"\n";
        }
    }
    std::cout << "Best time was for box_size = "<< least.first<< " and block_size = "<<least.second <<"\n";
} // We have gotten: Best time was for box_size = 3 and block_size = 8. 

void recreate_paper(){
    int d=5;
    int p=5;
    Data_vect data_mle = read_data();
    Vector theta_seq((d - 1) * p, 0.0);
    auto res_seq = Newton_ascent(theta_seq,data_mle,d,p);
    Vector result = res_seq.first;
    for (int i = 0; i < (d - 1) * p; i++) {
        std::cout << result[i] << std::endl;
    }
}

int main(){
    compare_seq();
    compare_parallel();
    //test_all_gradient();
    //test_all_newton();
    //tune_hyper_GPU();
    //recreate_paper();
    return 0;
} //Main pipeline