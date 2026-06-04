#include <vector>
#include <thread>
#include <cmath>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <numeric> 
using namespace std;
#include "../data.hpp"

// takes one family and adds its part to gradient 
void add_one_family(const Data_struct& fam, const vector<double>& theta,
                    vector<double>& gradient, int p, int d) {
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
}

// one core does all families
void compute_sequential(const vector<Data_struct>& data, const vector<double>& theta,
                        vector<double>& gradient, int p,int d) {
    int N = data.size();
    for (int i = 0; i < N; i++) {
        add_one_family(data[i], theta, gradient, p,d);
    }
}

// each worker does its part of families from start to end
void worker(const vector<Data_struct>& data, const vector<double>& theta,
            int start, int end, vector<double>& my_gradient, int p, int d) {
    for (int i = start; i < end; i++) {
        add_one_family(data[i], theta, my_gradient, p, d);
    }
}

// split families between T threads, then add up their gradients and hessians
void compute_parallel(const vector<Data_struct>& data, const vector<double>& theta, int T,
                      vector<double>& gradient,  int p, int d) {
    int N = data.size();
    int P = p * (d - 1);

    // one gradient and one hessian for each thread, all start at zero
    vector<vector<double>> partial_grad(T);
    for (int t = 0; t < T; t++) {
        partial_grad[t].resize(P, 0.0);
    }

    // start the threads
    vector<thread> threads;
    for (int t = 0; t < T; t++) {
        int start = t * N / T;
        int end = (t + 1) * N / T;
        threads.push_back(thread(worker, cref(data), cref(theta), start, end,
                                 ref(partial_grad[t]), p , d));
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
}


pair<vector<double>, bool> gradient_ascent_cpu(vector<double>& theta, vector<Data_struct>& data, int T, int d, int p, bool verbose, double step,  int max_iter, double eps){ //step and max_iter to be adjusted, possibly as an input of main.
    int N = data.size();
    for (int i=0; i<max_iter;i++){
        // Loss_Function_h tmp = Multinomial_logit(theta,data,d,p, h);
        vector<double> g(p*(d-1), 0.0);
        compute_parallel(data, theta, T, g, p,d);

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
        for (size_t j=0; j<theta.size();j++){
            theta[j] += step*g[j]/N;
        }
    }
    std::cout<<"max_iter = "<< max_iter << " reached!"<< std::endl;
    return std::pair(theta,false);
}
