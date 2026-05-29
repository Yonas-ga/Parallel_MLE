// Website from which i was inspired on how to parse the CSV, and learn the cpp specific methods/objects to do so.
// https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
// https://medium.com/@ryan_forrester_/reading-csv-files-in-c-how-to-guide-35030eb378ad
#include "data.hpp"
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
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
std::vector<std::string> split_csv_line(const std::string& line) {
    std::vector<std::string> row;
    std::stringstream tmp(line);
    std::string info;
    while (std::getline(tmp, info, ',')) {
        if (info.size() >= 2 && info.front() == '"' && info.back() == '"') { //values are for example string("0") instead of string(0) so stripping is necessary.
            info = info.substr(1, info.size() - 2);
        }
        row.push_back(info);
    }
    return row;
}

Data_vect read_data(const std::string& filename){
    std::ifstream file(filename);
    Data_vect entire_data;
    if (!file.is_open()) {
        std::cerr << "Oops, couldn't open file : " << filename << std::endl;
        return entire_data;
    }
    std::string line;
    std::getline(file, line); // first line with V...
    std::map<std::string,int> collumn;
    auto row = split_csv_line(line);
    for (int i = 0; i < (int)row.size(); ++i) {
        collumn[row[i]] = i;
    }

    while (std::getline(file, line)){ //for each row
        auto row = split_csv_line(line);
        double afdc = std::stod(row[collumn["V80"]]); //https://www.geeksforgeeks.org/cpp/cpp-program-for-string-to-double-conversion/ 
        double head_sex = std::stod(row[collumn["V119"]]); 
        double head_age = std::stod(row[collumn["V117"]]);
        double wife_age = std::stod(row[collumn["V118"]]);
        double head_race = std::stod(row[collumn["V383"]]);
        double wife_education = std::stod(row[collumn["V246"]]);
        double head_education = std::stod(row[collumn["V313"]]);
        double kids = std::stod(row[collumn["V398"]]);
        double get_afdc;
        if(afdc >0){
            get_afdc=1;
        } else{
            get_afdc=0;
        }
        

        if (head_sex==1 && wife_age==0){ //if single man, skip
            continue;
        } else if (head_sex==2){ //if head is woman
            double married =0;
            Vector data = {1.0, married, head_race, head_age, head_education, kids};
            entire_data.push_back({get_afdc, data});
        } else{ // head is man, who is married to woman;
            double married =1;
            Vector data = {1.0, married, head_race, wife_age, wife_education, kids};
            entire_data.push_back({get_afdc, data});
        }
    }
    return entire_data;
}

int main(){
    Data_vect data = read_data("Data/FAM1968_parsed_full.csv");
    std::cout << "Loaded rows: " << data.size() << std::endl;
}