#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

struct CSVData {
    Eigen::MatrixXd matrix;
    std::vector<std::string> columnNames;

    // Access a column by name as an Eigen vector
    Eigen::VectorXd col(const std::string& name) const {
        auto it = colIndex.find(name);
        if (it == colIndex.end())
            throw std::runtime_error("Column not found: " + name);
        return matrix.col(it->second);
    }

    // Access a single value by column name and row index
    double at(const std::string& name, int row) const {
        auto it = colIndex.find(name);
        if (it == colIndex.end())
            throw std::runtime_error("Column not found: " + name);
        return matrix(row, it->second);
    }

    int rows() const { return (int)matrix.rows(); }
    int cols() const { return (int)matrix.cols(); }

    std::map<std::string, int> colIndex; // name → column index
};

CSVData readCSV(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file: " + path);

    CSVData result;
    std::string line, cell;

    // --- Read header row ---
    if (!std::getline(file, line))
        throw std::runtime_error("Empty file: " + path);

    std::stringstream headerStream(line);
    int colIdx = 0;
    while (std::getline(headerStream, cell, ',')) {
        // Trim whitespace
        cell.erase(0, cell.find_first_not_of(" \t\r\n"));
        cell.erase(cell.find_last_not_of(" \t\r\n") + 1);
        result.columnNames.push_back(cell);
        result.colIndex[cell] = colIdx++;
    }

    // --- Read data rows ---
    std::vector<double> values;
    int rows = 0;
    const int cols = (int)result.columnNames.size();

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream lineStream(line);
        int current_cols = 0;
        while (std::getline(lineStream, cell, ',')) {
            cell.erase(0, cell.find_first_not_of(" \t\r\n"));
            cell.erase(cell.find_last_not_of(" \t\r\n") + 1);
            values.push_back(std::stod(cell));
            current_cols++;
        }
        if (current_cols != cols)
            throw std::runtime_error("Row " + std::to_string(rows + 1) +
                                     " has wrong column count");
        rows++;
    }

    using RMat = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
    result.matrix = Eigen::Map<RMat>(values.data(), rows, cols);

    return result;
}

double LL_i(int y, const Eigen::MatriXd& X, int k, const Eigen::MatriXd& W) {
    /* Computes the log-likelihood contribution of one observation*/

    std::unordered_set<double> unique_vals;
    for (int i = 0; i < y.size(); ++i) {
        unique_vals.insert(y[i]);
    } 
    int k = unique_vals.size();   

    // LL: Sum_k 
    Eigen::VectorXd beta = (X_b.transpose() * X_b).ldlt().solve(X_b.transpose() * y);
    return beta; // beta(0) = intercept, beta(1..) = coefficients
}

int main() {
    CSVData data = readCSV("Data/simple.csv");

    // Print column names
    std::cout << "Columns: ";
    for (const auto& name : data.columnNames)
        std::cout << "[" << name << "] ";
    std::cout << "\n\n";

    // Print full matrix
    std::cout << "Matrix:\n" << data.matrix << "\n\n";

    // Example: access a specific value
    // double val = data.at("price", 0);

    Eigen::VectorXd beta = LinReg(data.col("y"), data.col("x"));

    // Multiple predictors — stack columns into a matrix
    Eigen::MatrixXd X(data.rows(), 2);
    X.col(0) = data.col("x1");
    X.col(1) = data.col("x2");
    Eigen::VectorXd beta2 = LinReg(data.col("y"), X);

    std::cout << "Intercept: " << beta(0) << "\n";
    std::cout << "Coefficients:\n" << beta.tail(beta.size() - 1) << "\n";


}