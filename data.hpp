#include <chrono>
#include <vector>
#include <string>

using Vector = std::vector<double>; // Vector theta will be used as the arguments to optimize

struct Data_struct { // Tentative data structure, will be properly defined later 
    int outcome;
    Vector x; // Vector of the form (1.0 constant, married, race, age, education, kids)
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

struct SimulationResult {
    int N;
    int p;
    int d;

    bool cvg_h;
    bool cvg_g;

    Vector errors_h;
    Vector errors_g;
    std::chrono::microseconds runtime_h;
    std::chrono::microseconds runtime_g;
};

Data_vect read_data(); 

Data_vect read_loan_data(const std::string& filename);

double dot(Vector& a, Vector& b);

Vector solve(Vector& H, Vector& gradient, int d, int p);

std::pair<Vector, bool> gradient_ascent(Vector& theta, Data_vect& data, int d, int p, bool verbose = true, double step=0.07,  int max_iter=1e4, double eps=1e-3);
std::pair<Vector, bool> Newton_ascent(Vector& theta, Data_vect& data, int d, int p, bool verbose = true, double step=0.001,  int max_iter=1e4, double eps=1e-3);

std::pair<std::vector<double>, bool> gradient_ascent_cpu_lazy(std::vector<double>& theta, std::vector<Data_struct>& data, int T, int d, int p, bool verbose = true, double step=0.07,  int max_iter=1e6, double eps=1e-3);
std::pair<std::vector<double>, bool> Newton_ascent_cpu_lazy(std::vector<double>& theta, std::vector<Data_struct>& data, int T, int d, int p, bool verbose = true, double step=0.07,  int max_iter=1e6, double eps=1e-3);

std::pair<std::vector<double>, bool> gradient_ascent_cpu_cv(std::vector<double>& theta, std::vector<Data_struct>& data, int T, int d, int p, bool verbose = true, double step=0.07,  int max_iter=1e6, double eps=1e-3);
std::pair<std::vector<double>, bool> Newton_ascent_cpu_cv(std::vector<double>& theta, std::vector<Data_struct>& data, int T, int d, int p, bool verbose = true, double step=0.07,  int max_iter=1e6, double eps=1e-3);

std::pair<Vector, bool> gradient_ascent_gpu(Vector& theta, Data_vect& data, int d, int p, bool verbose = true, int box_size=3, int blockSize=8, double step=0.07,  int max_iter=1e4, double eps=1e-3);
std::pair<Vector, bool> Newton_ascent_gpu(Vector& theta, Data_vect& data, int d, int p, bool verbose=true, int box_size=3, int blockSize=8, double step=0.07,  int max_iter=1e4, double eps=1e-3);