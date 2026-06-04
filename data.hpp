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

Data_vect read_data(const std::string& filename); // Temporary, will probably replace with .hpp file

double dot(Vector& a, Vector& b){
    double res = 0;
    for (size_t i = 0; i < a.size(); ++i){
        res += a[i]*b[i];
    }
    return res;
}