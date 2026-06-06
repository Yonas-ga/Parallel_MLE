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
#include <mutex>
#include <condition_variable>

// takes one family and adds its part to gradient 
void add_one_family_cv(const Data_struct& fam, const vector<double>& theta,
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


// each worker does its part of families from start to end
void worker_cv(const vector<Data_struct>& data, const vector<double>& theta,
            int start, int end, vector<double>& my_gradient, int p, int d,int T, std::mutex& mtx,
            std::condition_variable& cv_start, std::condition_variable& cv_done, bool& converged, int& finished_workers, int& iter){
    int my_iter =0;
    while(true){
        {
            unique_lock<mutex> lock(mtx);
            while(my_iter==iter && converged == false){
                cv_start.wait(lock);
            }
            if (converged==true){
                return;
            }
            my_iter = iter;
        }
        for(int q=0;q<p*(d-1);q++){
            my_gradient[q]=0.0;
        }
        for (int i = start; i < end; i++) {
            add_one_family_cv(data[i], theta, my_gradient, p, d);
        }
        {
            std::lock_guard<std::mutex> lock(mtx);
            finished_workers += 1;
            if(finished_workers==T){ //if last thread to finish, tell "main" to continue
                cv_done.notify_one();
            }
        }
    }
}


pair<vector<double>, bool> gradient_ascent_cpu_cv(vector<double>& theta, vector<Data_struct>& data, int T, int d, int p, bool verbose, double step,  int max_iter, double eps){ //step and max_iter to be adjusted, possibly as an input of main.
    int global_iter =0;
    int N = data.size();
    std::mutex mtx;
    std::condition_variable cv_start;
    std::condition_variable cv_done;
    bool converged = false;
    int finished_workers =0;

    vector<vector<double>> partial_grad(T);
    for (int t = 0; t < T; t++) {
        partial_grad[t].resize(p*(d-1), 0.0);
    }

    vector<thread> threads;
    for (int t = 0; t < T; t++) {
        int start = t * N / T;
        int end = (t + 1) * N / T;
        threads.push_back(thread(worker_cv, cref(data), cref(theta), start, end,
                                 ref(partial_grad[t]), p , d, T, ref(mtx), ref(cv_start), ref(cv_done), ref(converged), ref(finished_workers), ref(global_iter)));
    }

    for (int i=0; i<max_iter;i++){
        vector<double> g(p*(d-1), 0.0);
        // compute parallel
        {
            std::lock_guard<std::mutex> lock(mtx);
            finished_workers = 0;
            global_iter +=1;
        }
        cv_start.notify_all();
        {
            unique_lock<mutex> lock(mtx);
            while (finished_workers < T){
                cv_done.wait(lock);
            }
        }
        for (int t = 0; t < T; t++) {
            for (int k = 0; k < p*(d-1); k++) {
                g[k] += partial_grad[t][k]/N;
            }
        }

        if (verbose)  std::cout<<"||Gradient_CPU_CV|| = "<< sqrt(dot(g,g)) << std::endl;

        
        if (sqrt(dot(g,g)) <eps) {
            if (verbose) std::cout<<"eps = "<< eps << " reached!"<< std::endl;
            {
                lock_guard<mutex> lock(mtx);
                converged = true;
            }
            cv_start.notify_all();
            for (int t = 0; t < T; t++) {
                threads[t].join();
            }
            return pair(theta,true);
        }
        for (size_t j=0; j<theta.size();j++){
            theta[j] += step*g[j];
        }
    }
    {
        lock_guard<mutex> lock(mtx);
        converged = true; //even if not converged, just to kill all threads.
    }
    cv_start.notify_all();
    for (int t = 0; t < T; t++) {
        threads[t].join();
    }
    std::cout<<"max_iter = "<< max_iter << " reached!"<< std::endl;
    return std::pair(theta,false);
}
