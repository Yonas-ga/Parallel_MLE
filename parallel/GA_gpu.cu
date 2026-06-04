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
void gradient_aux_V1( double* X , int* y , double* theta, double* gradient, int N, int p, int d, int box_size, double* global_tmp_gradients,double* global_tmp, double* global_P ){  //V1 because one thread ---- one data point (will probably try to do blocks of data points)
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
    for (int q = 0; q < (p*(d-1)); q++) {
        tmp_gradient[q] = 0.0;
    }
    for(int i = start;i<end;i++){
        double* tmp = &global_tmp[index*d];
        double* P= &global_P[index*d];
        for (int q = 0; q<d;q++){
            tmp[q]=0.0;
            P[q]=0.0;
        }
        double denom = 0;
        for (size_t j = 0; j < d-1; ++j){
            for (size_t k = 0; k < p; ++k){
                tmp[j] += X[i*p +k] *  theta[p*j + k];
            }
            denom += exp(tmp[j]);
        }
        tmp[d-1] = 0.0;
        denom += 1.0;
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
    }
    for(int q=0;q<(p*(d-1));q++){
        atomicAdd(&gradient[q], tmp_gradient[q]);
    }
}

std::pair<Vector, bool> gradient_ascent_gpu(Vector& theta, Data_vect& data, int d, int p, double step,  int max_iter, double eps){
    int N = data.size();
    int box_size = 8; // Number of data points checked for each thread
    int blockSize = 256; // TODO: optimize ?
    int numberThreads = (N + box_size - 1) / box_size;
    int gridSize = (numberThreads + blockSize - 1) / blockSize;
    double X[N*p];
    int y[N];
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
    cudaMalloc(&tmp_X, N * p * sizeof(double));
    cudaMalloc(&tmp_y, N * sizeof(int));
    cudaMalloc(&tmp_theta, (p*(d-1)) * sizeof(double));
    cudaMalloc(&tmp_gradient, (p*(d-1)) * sizeof(double));
    cudaMalloc(&global_tmp_gradients,numberThreads *(p*(d-1))* sizeof(double));
    cudaMalloc(&global_tmp, d*numberThreads *sizeof(double));
    cudaMalloc(&global_P, d*numberThreads *sizeof(double));
    cudaMemcpy(tmp_X, &X[0], N * p * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(tmp_y, &y[0], N * sizeof(int), cudaMemcpyHostToDevice);
    std::vector<double> gradient(p*(d-1));

    
    for (int iter = 0; iter < max_iter; iter++){
        cudaMemset(global_tmp_gradients, 0, numberThreads *(p*(d-1))* sizeof(double));
        cudaMemcpy(tmp_theta, &theta[0], (p*(d-1))* sizeof(double), cudaMemcpyHostToDevice);
        cudaMemset(tmp_gradient, 0, (p*(d-1))* sizeof(double));
        gradient_aux_V1<<<gridSize, blockSize>>>(tmp_X, tmp_y, tmp_theta, tmp_gradient, N, p, d, box_size, global_tmp_gradients, global_tmp, global_P);
        cudaMemcpy(gradient.data(), tmp_gradient, (p*(d-1))* sizeof(double), cudaMemcpyDeviceToHost);
        double norm = 0.0;
        for (double g : gradient){
            norm += g*g;
        }
        norm = sqrt(norm);
        std::cout << "||Gradient|| = " << norm << std::endl;
        if (norm < eps) {
            cudaFree(tmp_X);
            cudaFree(tmp_y);
            cudaFree(tmp_theta);
            cudaFree(tmp_gradient);
            cudaFree(global_tmp_gradients);
            cudaFree(global_tmp);
            cudaFree(global_P);
            return {theta, true};
        }
        for (int j = 0; j < (p*(d-1)); j++) {
            theta[j] += step * gradient[j];
        }
    }
    cudaFree(tmp_X);
    cudaFree(tmp_y);
    cudaFree(tmp_theta);
    cudaFree(tmp_gradient);
    cudaFree(global_tmp_gradients);
    cudaFree(global_tmp);
    cudaFree(global_P);
    return {theta, false};
}