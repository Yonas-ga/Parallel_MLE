#include <vector>
#include <cmath>

using Vector = std::vector<double>; // Vector theta will be used as the arguments to optimize
using Data_vect = std::vector<Data_struct>;

struct Data_struct { // Tentative data structure, will be properly defined later 
    double outcome;
    Vector x;
};

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
Loss_Function_Result Multinomial_logit(){  //Computes de loss function, Multinomial_logit is the one used in the reference paper.

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
Vector gradient_descent(Vector& theta, Data_vect& data, double step=0.01, int max_iter=1000){ //step and max_iter to be adjusted, possibly as an input of main.
    for (int i=0; i<max_iter;i++){
        Loss_Function_Result tmp = least_square(theta,data);
        for (j=0; j<theta.size();j++){
            theta[j] -= step*tmp.gradient[j];
        }
    }
    return theta;
}

void main(){} // Pipeline

