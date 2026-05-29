#include <vector>
#include <cmath>
#include <iostream>


///// TO DO: 
// Make solve


using Vector = std::vector<double>; // Vector theta will be used as the arguments to optimize

struct Data_struct { // Tentative data structure, will be properly defined later 
    double outcome;
    Vector x;
};
using Data_vect = std::vector<Data_struct>;
struct Loss_Function_Result {
    double value;
    Vector gradient;
};

struct Loss_Function_h {
    double value;
    Vector gradient;
    Vector H;
};

// Helper Functions

double dot(Vector& a, Vector& b){
    double res = 0;
    for (size_t i = 0; i < a.size(); ++i){
        res += a[i]*b[i];
    }
    return res;
}

Vector solve(Vector& H, Vector& gradient, int d, int p){
    /// delta = solve (H * delta  = gradient);
    //      solve L x (L.T x delta) =: L x y = gradient
    // 1. Find L (lower matrix) s.t L x L.T = H
    //      H needs to be positive definite (could imporve by putting a plan B)
    // 2. Find y (vector) s.t. L x y = gradient
    // 3. Find delta (vector) s.t. (L.T x delta) = y

    // 1. Finding L
    int n = p*(d-1);
    Vector L(H.size(),0.0);
    // For all   j, L[j][j] = sqrt(H[j][j] - Sum_{0<k<n+1} L[j][k]*L[j][k])
    // For all i,j, L[i][j] = (H[i][j] - Sum_{0<k<j} L[i][k] L[j][k])/ L[j][j]

    for (size_t j = 0; j < n; ++j){
        double Sum_for_jj = 0.0;
        for (size_t k = 0; k < j; ++k){
            Sum_for_jj += L[j*n + k]*L[j*n + k];
        }

        if (H[j*n+j] - Sum_for_jj < 0){
            std::cout<< "Hessian NOT Negative"  << std::endl;
            return Vector{};
        }
        L[j*n + j] = sqrt(H[j*n+j] - Sum_for_jj);

        for (size_t i = j+1; i < n; ++i){
            double Sum_for_ij = 0.0;
            for (size_t k = 0; k < j; ++k){
                Sum_for_ij += L[i*n + k]*L[j*n + k];
            }
            L[i*n + j] += (H[i*n + j] - Sum_for_ij)/L[j*n+j];
        }
    }

    // 2. Finding y 
    Vector y(gradient.size(),0.0);
    // for all i, y[i] = (gradient[k] - Sum_{0<k<i-1} L[i][k] y[k])/L[i][i]
    for (size_t i = 0; i < n; ++i){
            double Sum_for_i = 0.0;
            for (size_t k = 0; k < i; ++k){
                Sum_for_i += L[i*n + k]*y[k];
            }
            y[i] = (gradient[i] - Sum_for_i)/L[i*n+i];
        }

    // 2. Finding delta
    Vector delta(gradient.size(),0.0);
    // for all i, delta[i] = (y[k] - Sum_{0<k<i-1} L[k][i] delta[k])/L[i][i]
    for (int i = n-1; i >= 0; --i){
        double Sum_for_i = 0.0;
        for (size_t k = i+1; k < n; ++k){
            Sum_for_i += L[k*n + i] * delta[k];
        }
        delta[i] = (y[i] - Sum_for_i)/L[i*n+i];
    }

    return delta;
}


// MLE functions
Loss_Function_h Multinomial_logit(Vector& theta, std::vector<Data_struct>& data, int d, int p){  //Computes de loss function, Multinomial_logit is the one used in the reference paper.
    // Multinomial Logit
    // Log Likelihood = Sum_{observtion} Sum_{k} Indicator{Output=k} [X_k \theta_k - log(Sum_{j} exp(X_j \theta_j))

    double ll = 0;
    Vector gradient(theta.size(), 0.0);
    Vector H(theta.size()*theta.size(), 0.0);

    for (Data_struct& data_point : data){

        std::vector<double> lcom(d, 0.0);
        std::vector<double> P(d, 0.0);
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
        

        /// Log Loss
        ll += lcom[data_point.outcome] - log(denom);


        /// Gradient
        for (size_t j = 0; j < d-1; ++j){
            double ind = 0;
            if (j ==data_point.outcome){ 
                ind = 1;
            }
            for(size_t k = 0; k<p; k++){
                gradient[j*p + k] += data_point.x[k] * (ind - P[j]);
            }
        }

        /// Hessian
        for (size_t j = 0; j < d-1; ++j){
            for (size_t l = 0; l < d-1; ++l){
                double scal = 0.0;
                if (j ==l){ 
                    scal = P[j]*(1.0-P[j]);
                }
                else{
                    scal = -P[j]*P[l];
                }
                for(size_t k1 = 0; k1<p; k1++){
                    for(size_t k2 = 0; k2<p; k2++){
                        H[(j*p + k1)*(p*(d-1)) + l*p + k2] += scal * data_point.x[k1] * data_point.x[k2];
                    }
                }
            }
        }
    }



    Loss_Function_h res{ll, gradient, H} ;
    return res;
} 

Vector gradient_ascent(Vector& theta, Data_vect& data, int d, int p, bool h = true, double step=0.01,  int max_iter=1e3, double eps=1e-10){ //step and max_iter to be adjusted, possibly as an input of main.
    for (int i=0; i<max_iter;i++){
        Loss_Function_h tmp = Multinomial_logit(theta,data,d,p);
        std::cout<<"||Gradient|| = "<< sqrt(dot(tmp.gradient,tmp.gradient)) << std::endl;

        
        if (dot(tmp.gradient,tmp.gradient)<eps*eps) {
            std::cout<<"eps = "<< eps << " reached!"<< std::endl;
            std::cout<< "------------------------------------------"  << std::endl;
            int j = 0;
                for (double v : tmp.H) {
                    if (j==p*(d-1)){
                        std::cout << std::endl;
                        j=0;
                    }
                    std::cout << v << " ";
                    j ++;
                }
                std::cout << std::endl;
            std::cout<< "------------------------------------------" << std::endl;
            return theta;
        }
        if (!h){
            for (size_t j=0; j<theta.size();j++){
                theta[j] += step*tmp.gradient[j];
            }
        }
        else{
            Vector delta(theta.size(), 0.0);
            delta = solve (tmp.H, tmp.gradient, d,p);
            if (delta.empty()){
                for (size_t j=0; j<theta.size();j++){
                    theta[j] += step*tmp.gradient[j];
                }
            }
            else {
                for (size_t j=0; j<theta.size();j++){
                    theta[j] += delta[j];
                }
            }
            
        }
    }
    std::cout<<"max_iter = "<< max_iter << " reached!"<< std::endl;
    return theta;
}


int main(){
    int N; // Number of observations
    int d = 3; // Number of possible outcomes including base
    int p = 2; // Number of features


    // Testing Khaled's sequential MLE
    Vector theta_mle ((d-1)*p, 0.0);
    // True theta: beta_1=[1.0,-1.0], beta_2=[-1.0,1.0], beta_3=[0,0] (baseline)
    // k=2 features, d=3 alternatives

    std::vector<Data_struct> data_mle = {
        {0, { 0.2, -1.4}},  
        {1, { 0.6, -0.1}},
        {1, {-0.6,  0.4}},   
        {0, { 0.0, -0.7}},
        {0, { 1.2,  0.5}},
        {2, { 1.2,  0.3}},
        {0, {-1.1, -1.4}},
        {1, {-0.9,  0.2}},
        {1, {-1.3, -0.7}},
        {2, {-0.2, -0.3}},
    };
    
    Vector result_mle = gradient_ascent(theta_mle, data_mle, d, p); // beta_1=[1.0,-1.0], beta_2=[-1.0,1.0], beta_3=[0,0] 
    for (double v : result_mle) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

} // Pipeline

