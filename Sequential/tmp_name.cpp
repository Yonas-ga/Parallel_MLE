
#include <vector>
#include <cmath>
#include <iostream>
#include "../data.hpp"

///// TO DO: 
//          make sense of i,j,k
//          j \in {1,...,d} where j is an outcome
//          k \in {1,...,p} where k is a feature
//          rethink data struct (maybe numpy eq)



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

Vector gradient_ascent(Vector& theta, Data_vect& data, int d, int p, double step=1e-5,  int max_iter=500, double eps=1){ //step and max_iter to be adjusted, possibly as an input of main.
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
    int d = 5; // Number of possible outcomes including base
    int p = 3; // Number of features

    // Testing Yonas' OLS by gradient descent
    Vector theta_OLS(2,0.0);
    Data_vect data_OLS = {
                        {3, {1.0, 2.0}},
                        {2, {1.0, 1.0}},
                        {4, {1.0, 3.0}}
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
    
    std::vector<Data_struct> data_paper = read_data("Data/FAM1968_parsed_full.csv");
    /*
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
    */
    std::vector<Data_struct> data_mle;
    for (int i = 0; i < 10000; i++) {
        double x1 = (rand() % 2000 - 1000) / 1000.0;
        double x2 = (rand() % 2000 - 1000) / 1000.0;
        double x3 = (rand() % 2000 - 1000) / 1000.0;
        double x4 = (rand() % 2000 - 1000) / 1000.0;
        double x5 = 1.0;

        int outcome;

        double s0 = 2*x1 - x2;
        double s1 = -x1 + 2*x2;
        double s2 = x3;
        double s3 = -x4;

        if (s0 >= s1 && s0 >= s2 && s0 >= s3 && s0 >= 0){
            outcome = 0;
        } else if (s1 >= s2 && s1 >= s3 && s1 >= 0){
            outcome = 1;
        } else if (s2 >= s3 && s2 >= 0){
            outcome = 2;
        } else if (s3 >= 0){
            outcome = 3;
        } else{
            outcome = 4; 
        }
        //data_mle.push_back({outcome, {x1,x2,x3,x4,x5}});
    }
    Vector true_theta = {
    2.0, -1.0, 0.0,  
    -1.0,  2.0,  0.0,  
    1.0,  1.0,  0.0,   
    -1.0, -1.0,  0.0  
    };
    for (int i = 0; i < 10000; i++) {

        double x1 = (rand() % 2000 - 1000) / 1000.0;
        double x2 = (rand() % 2000 - 1000) / 1000.0;

        Vector x = {x1, x2, 1.0};

        std::vector<double> score(d, 0.0);
        double denom = 1.0;

        for (int j = 0; j < d-1; j++) {
            for (int k = 0; k < p; k++) {
                score[j] += x[k] * true_theta[j*p + k];
            }
            denom += exp(score[j]);
        }

        std::vector<double> prob(d);
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
    Vector result_mle = gradient_ascent(theta_mle, data_mle, d, p); // Expected output theta = (1, 1)
    for (double v : result_mle) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

} // Pipeline

