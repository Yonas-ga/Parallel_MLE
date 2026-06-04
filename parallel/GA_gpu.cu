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
void gradient_aux_V1( double* X , int* y , double* theta, double* gradient, int N,int p, int d ){  //V1 because one thread ---- one data point (will probably try to do blocks of data points)
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i >= N) {
        return;
    }
    double tmp[d];
    double P[d];
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
            gradient[j*p + k] += (X[i*p +k] * (ind - P[j]))/N; // TODO check if we need atomic add ??
        }
    }
}

std::pair<Vector, bool> gradient_ascent(Vector& theta, Data_vect& data, int d, int p, double step=0.07,  int max_iter=1e4, double eps=1e-3){
    int N = data.size();

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
    cudaMalloc(&tmp_X, N * p * sizeof(double));
    cudaMalloc(&tmp_y, N * sizeof(int));
    cudaMalloc(&tmp_theta, P * sizeof(double));
    cudaMalloc(&tmp_gradient, P * sizeof(double));
    cudaMemcpy(tmp_X, &X[0], N * p * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(tmp_y, &y[0], N * sizeof(int), cudaMemcpyHostToDevice);
    std::vector<double> gradient(p*(d-1));

    int blockSize = 256; // TODO: optimize ?
    int gridSize = (N + blockSize - 1) / blockSize;
    for (int iter = 0; iter < max_iter; iter++){
        cudaMemcpy(tmp_theta, &theta[0], (p*(d-1))* sizeof(double), cudaMemcpyHostToDevice);
        cudaMemset(tmp_gradient, 0, (p*(d-1))* sizeof(double));
        gradient_aux_V1<<<gridSize, blockSize>>>(tmp_X, tmp_y, tmp_theta, tmp_gradient, N, p, d);
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
    return {theta, false};
}