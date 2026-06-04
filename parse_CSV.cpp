// Website from which i was inspired on how to parse the CSV, and learn the cpp specific methods/objects to do so.
// https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
// https://medium.com/@ryan_forrester_/reading-csv-files-in-c-how-to-guide-35030eb378ad

#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "../data.hpp"

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
        double head_hour_work = std::stod(row[collumn["V47"]]);
        double wife_hour_work = std::stod(row[collumn["V53"]]);
        int outcome;
        if (head_race==0 || head_race==2){
            head_race=0; //white
        } else{
            head_race=1;//black/non-white
        }

        if (head_sex==1 && wife_age==0){ //if single man, skip
            continue;
        } else if (head_sex==2){ //if head is woman
            double married =0;
            double working;
            if (head_hour_work>0){
                working=1;
            } else {
                working=0;
            }
            if (afdc>0){
                outcome = 3;
            } else if (working==1){
                outcome = 1;
            } else{
                outcome = 4;
            }

            Vector data = {1.0, head_age,head_education,head_race, kids};
            entire_data.push_back({outcome, data});
        } else{ // head is man, who is married to woman;
            double married =1;
            double working;
            if (wife_hour_work>0){
                working=1;
                outcome = 2;
            } else {
                working=0;
                outcome = 0;
            }
            Vector data = {1.0,wife_age, wife_education,head_race,   kids};
            entire_data.push_back({outcome, data});
        }
    }
    std::vector<int> counts(5, 0);
    for (auto& obs : entire_data) {
        counts[obs.outcome]++;
    }
    for (int j = 0; j < 5; ++j) {
        std::cout << "Outcome " << j << ": " << counts[j] << std::endl;
    }
    return entire_data;
}

