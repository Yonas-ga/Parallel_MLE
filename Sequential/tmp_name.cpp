#include "data.hpp"
#include <vector>
#include <cmath>
#include <iostream>


///// TO DO: 
//          make sense of i,j,k
//          j \in {1,...,d} where j is an outcome
//          k \in {1,...,p} where k is a feature
//          rethink data struct (maybe numpy eq)
using Vector = std::vector<double>; // Vector theta will be used as the arguments to optimize

struct Data_struct { // Tentative data structure, will be properly defined later 
    double outcome;
    Vector x; // Vector of the form (1.0 constant, married, race, age, education, kids)
};
using Data_vect = std::vector<Data_struct>;
struct Loss_Function_Result {
    double value;
    Vector gradient;
};
// Auxiliary functions

double dot(Vector& a, Vector& b){
    double res = 0;
    for (size_t i = 0; i < a.size(); ++i){
        res += a[i]*b[i];
    }
    return res;
}


// MLE functions
Loss_Function_Result Multinomial_logit(Vector& theta, std::vector<Data_struct>& data, int d, int p){  //Computes de loss function, Multinomial_logit is the one used in the reference paper.
    // Multinomial Logit
    // Log Likelihood = Sum_{observtion} Sum_{k} Indicator{Output=k} [X_k \theta_k - log(Sum_{j} exp(X_j \theta_j))}

    double ll = 0;
    Vector gradient(theta.size(), 0.0);

    for (Data_struct& data_point : data){

        std::vector<double> lcom(d);
        std::vector<double> P(d);
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
        
        ll += lcom[data_point.outcome] - log(denom);

        for (size_t j = 0; j < d-1; ++j){
            double ind = 0;
            if (j ==data_point.outcome){ 
                ind = 1;
            }
            for(size_t k = 0; k<p; k++){
                gradient[j*p + k] += data_point.x[k] * (ind - P[j]);
            }
        }
    }

    Loss_Function_Result res{ll, gradient} ;
    return res;
} 

Loss_Function_Result least_square(Vector& theta, Data_vect& data){
    double loss = 0;
    Vector gradient(theta.size(), 0); // Initialise the vector gradient with size theta.size() and all elements of value 0

    for (auto& data_point : data){
        double tmp = dot(data_point.x, theta);
        double err = tmp-data_point.outcome;
        loss += err*err;
        for (size_t i = 0; i < theta.size(); ++i){
            gradient[i] += err*data_point.x[i];
        }
    }
    Loss_Function_Result res{loss,gradient};
    return res;
}

// TODO: Change to input loss function
Vector gradient_descent(Vector& theta, Data_vect& data, double step=0.01,  int max_iter=1e4, double eps=1e-05){ //step and max_iter to be adjusted, possibly as an input of main.
    for (int i=0; i<max_iter;i++){
        Loss_Function_Result tmp = least_square(theta,data);
        if (dot(tmp.gradient,tmp.gradient)<eps*eps) {
            std::cout<<"eps = "<< eps << " reached!"<< std::endl;
            return theta;
        }
        for (size_t j=0; j<theta.size();j++){
            theta[j] -= step*tmp.gradient[j];
        }
    }

    std::cout<<"max_iter = "<< max_iter << " reached!"<< std::endl;
    return theta;
}

Vector gradient_ascent(Vector& theta, Data_vect& data, int d, int p, double step=0.01,  int max_iter=1e4, double eps=1e-05){ //step and max_iter to be adjusted, possibly as an input of main.
    for (int i=0; i<max_iter;i++){
        Loss_Function_Result tmp = Multinomial_logit(theta,data,d,p);
        std::cout<<"||Gradient|| = "<< sqrt(dot(tmp.gradient,tmp.gradient)) << std::endl;
        if (dot(tmp.gradient,tmp.gradient)<eps*eps) {
            std::cout<<"eps = "<< eps << " reached!"<< std::endl;
            return theta;
        }
        for (size_t j=0; j<theta.size();j++){
            theta[j] += step*tmp.gradient[j];
        }
    }
    std::cout<<"max_iter = "<< max_iter << " reached!"<< std::endl;
    return theta;
}


int main(){
    int N; // Number of observations
    int d = 3; // Number of possible outcomes including base
    int p = 2; // Number of features

    // Testing Yonas' OLS by gradient descent
    Vector theta_OLS(2,0.0);
    Data_vect data_OLS = {
                        {3.0, {1.0, 2.0}},
                        {2.0, {1.0, 1.0}},
                        {4.0, {1.0, 3.0}}
                    };
    Vector result_OLS = gradient_descent(theta_OLS, data_OLS); // Expected output theta = (1, 1)
    for (double v : result_OLS) {
        std::cout << v << " ";
    }
    std::cout << std::endl;


    // Testing Khaled's sequential MLE
    // Testing Yonas' OLS by gradient descent
    Vector theta_mle ((d-1)*p, 0.0);
    // True theta: beta_1=[1.0,-1.0], beta_2=[-1.0,1.0], beta_3=[0,0] (baseline)
    // k=2 features, d=3 alternatives

    std::vector<Data_struct> data_mle = {
        {0, { 0.2, -1.4}},   // high x1, low x2  → alt 1 likely ✓
        {1, { 0.6, -0.1}},
        {1, {-0.6,  0.4}},   // low x1, high x2  → alt 2 likely ✓
        {0, { 0.0, -0.7}},
        {0, { 1.2,  0.5}},
        {2, { 1.2,  0.3}},
        {0, {-1.1, -1.4}},
        {1, {-0.9,  0.2}},
        {1, {-1.3, -0.7}},
        {2, {-0.2, -0.3}},
    };
    
    Vector result_mle = gradient_ascent(theta_mle, data_mle, d, p); // Expected output theta = (1, 1)
    for (double v : result_mle) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

} // Pipeline

