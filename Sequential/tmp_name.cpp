#include <vector>

using Vector = std::vector<double>;

struct Data_struct { // Tentative data structure, will be properly defined later 
    int outcome;
    Vector x;
}

struct Loss_Function_Result {
    double value;
    Vector gradient;
};

Loss_Function_Result Multinomial_logit(){} //Computes de loss function

Vector gradient_descent(){}

void main(){} // Pipeline

