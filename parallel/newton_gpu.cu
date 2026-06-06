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

__global__
void Newton_aux( double* X , int* y , double* theta, double* gradient, int N, int p, int d, int box_size, double* global_tmp_gradients,double* global_tmp, double* global_P, double* H,double* global_H){  //V1 because one thread ---- one data point (will probably try to do blocks of data points)
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    int start = index*box_size;
    if (start >= N) {
        return;
    }
    int end = start+box_size;
    if(end>N){
        end = N;
    }
    double* tmp_gradient = &global_tmp_gradients[index*(p*(d-1))];
    double* tmp_H = &global_H[index*(p*(d-1))*(p*(d-1))];
    for (int q = 0; q < (p*(d-1)); q++) {
        tmp_gradient[q] = 0.0;
        for(int q_=0;q_<(p*(d-1));q_++){
            tmp_H[q*(p*(d-1)) + q_]=0.0;
        }
    }
    
    for(int i = start;i<end;i++){
        double* tmp = &global_tmp[index*d];
        double* P= &global_P[index*d];
        for (int q = 0; q<d;q++){
            tmp[q]=0.0;
            P[q]=0.0;
        }
        double denom = 1.0;
        for (size_t j = 0; j < d-1; ++j){
            for (size_t k = 0; k < p; ++k){
                tmp[j] += X[i*p +k] *  theta[p*j + k];
            }
            denom += exp(tmp[j]);
        }
        for (size_t j = 0; j < d; ++j){
            P[j] = exp(tmp[j])/denom;
        }
        for (size_t j = 0; j < d-1; ++j){
            double ind = 0;
            if (j ==y[i]){ 
                ind = 1;
            }
            for(size_t k = 0; k<p; k++){
                tmp_gradient[j*p + k] += (X[i*p +k] * (ind - P[j]))/N;
            }
        }
        for (int j = 0; j < d - 1; j++) {
            for (int l = 0; l < d - 1; l++) {
                double scal = 0.0;
                if (j == l) {
                    scal = P[j] * (1.0 - P[j]);
                } else {
                    scal = -P[j] * P[l];
                }
                for (int k1 = 0; k1 < p; k1++) {
                    for (int k2 = 0; k2 < p; k2++) {
                        int row = j * p + k1;
                        int col = l * p + k2;
                        tmp_H[row *(p*(d-1)) + col] += (scal * X[i*p +k1] * X[i*p +k2])/N;
                    }
                }
            }
        }
    }
    for(int q=0;q<(p*(d-1));q++){
        atomicAdd(&gradient[q], tmp_gradient[q]);
        for(int q_=0;q_<(p*(d-1));q_++){
            atomicAdd(&H[q*(p*(d-1)) + q_], tmp_H[q*(p*(d-1)) + q_]);
        }
    }
}

std::pair<Vector, bool> Newton_ascent_gpu(Vector& theta, Data_vect& data, int d, int p, bool verbose, int box_size, int blockSize, double step,  int max_iter, double eps){
    int N = data.size();
    int numberThreads = (N + box_size - 1) / box_size;
    int gridSize = (numberThreads + blockSize - 1) / blockSize;
    std::vector<double> X(N*p);
    std::vector<int> y(N);
    for (int i = 0; i < N; i++) {
        y[i] = data[i].outcome;
        for (int k = 0; k < p; k++) {
            X[i * p + k] = data[i].x[k];
        }
    }
    double* tmp_X;
    double* tmp_theta;
    double* tmp_gradient;
    int* tmp_y;
    double* global_tmp_gradients;
    double* global_tmp;
    double* global_P;
    double* tmp_H;
    double* global_H;
    cudaMalloc(&tmp_X, N * p * sizeof(double));
    cudaMalloc(&tmp_y, N * sizeof(int));
    cudaMalloc(&tmp_theta, (p*(d-1)) * sizeof(double));
    cudaMalloc(&tmp_gradient, (p*(d-1)) * sizeof(double));
    cudaMalloc(&global_tmp_gradients,numberThreads *(p*(d-1))* sizeof(double));
    cudaMalloc(&global_tmp, d*numberThreads *sizeof(double));
    cudaMalloc(&global_P, d*numberThreads *sizeof(double));
    cudaMalloc(&tmp_H, (p*(d-1))*(p*(d-1))*sizeof(double));
    cudaMalloc(&global_H, (p*(d-1))*(p*(d-1))*numberThreads *sizeof(double));
    cudaMemcpy(tmp_X, &X[0], N * p * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(tmp_y, &y[0], N * sizeof(int), cudaMemcpyHostToDevice);
    std::vector<double> gradient(p*(d-1));
    std::vector<double> H(p*(d-1)*p*(d-1), 0.0);

    
    for (int iter = 0; iter < max_iter; iter++){
        cudaMemset(global_tmp_gradients, 0, numberThreads *(p*(d-1))* sizeof(double));
        cudaMemcpy(tmp_theta, &theta[0], (p*(d-1))* sizeof(double), cudaMemcpyHostToDevice);
        cudaMemset(tmp_gradient, 0, (p*(d-1))* sizeof(double));
        cudaMemset(global_H, 0, (p*(d-1))*(p*(d-1))*numberThreads *sizeof(double));
        cudaMemset(tmp_H, 0, (p*(d-1))*(p*(d-1))*sizeof(double));
        Newton_aux<<<gridSize, blockSize>>>(tmp_X, tmp_y, tmp_theta, tmp_gradient, N, p, d, box_size, global_tmp_gradients, global_tmp, global_P,tmp_H,global_H);
        cudaMemcpy(gradient.data(), tmp_gradient, (p*(d-1))* sizeof(double), cudaMemcpyDeviceToHost);
        cudaMemcpy(H.data(), tmp_H,(p*(d-1))*(p*(d-1))*sizeof(double),cudaMemcpyDeviceToHost);
        double norm = 0.0;
        for (double g : gradient){
            norm += g*g;
        }
        norm = sqrt(norm);
        if (verbose){
            std::cout << "||Gradient_GPU|| = " << norm << std::endl;
        }
        if (norm < eps) {
            cudaFree(tmp_X);
            cudaFree(tmp_y);
            cudaFree(tmp_theta);
            cudaFree(tmp_gradient);
            cudaFree(global_tmp_gradients);
            cudaFree(global_tmp);
            cudaFree(global_P);
            cudaFree(global_H);
            cudaFree(tmp_H);
            return {theta, true};
        }
        vector<double> delta(theta.size(), 0.0);
        delta = solve(H, gradient, d,p);
        if (delta.empty()){
            for (size_t j=0; j<theta.size();j++){
                theta[j] += step*gradient[j]/N;
            }
        }
        else {
            for (size_t j=0; j<theta.size();j++){
                theta[j] += delta[j];
            }
        }
    }
    cudaFree(tmp_X);
    cudaFree(tmp_y);
    cudaFree(tmp_theta);
    cudaFree(tmp_gradient);
    cudaFree(global_tmp_gradients);
    cudaFree(global_tmp);
    cudaFree(global_P);
    cudaFree(global_H);
    cudaFree(tmp_H);
    return {theta, false};
}