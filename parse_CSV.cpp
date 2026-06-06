// Website from which i was inspired on how to parse the CSV, and learn the cpp specific methods/objects to do so.
// https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
// https://medium.com/@ryan_forrester_/reading-csv-files-in-c-how-to-guide-35030eb378ad

#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "data.hpp"

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

Data_vect read_data(){
    std::string filenames[8] = {"Data/parsed/FAM1968_parsed_full.csv","Data/parsed/FAM1969_parsed_full.csv","Data/parsed/FAM1972_parsed_full.csv","Data/parsed/FAM1976_parsed_full.csv","Data/parsed/FAM1979_parsed_full.csv","Data/parsed/FAM1982_parsed_full.csv","Data/parsed/FAM1985_parsed_full.csv","Data/parsed/FAM1988_parsed_full.csv"};
    std::string _afdc[8] = {"V80", "V523", "V2512", "V4392", "V6413", "V8288", "V11427", "V14943"};
    std::string _head_sex[8] = {"V119", "V1010", "V2543", "V4437", "V6463", "V8353", "V11607", "V15131"};
    std::string _head_age[8] = {"V117", "V1008", "V2542", "V4436", "V6462", "V8352", "V11606", "V15130"};
    std::string _wife_age[8] = {"V118", "V1011", "V2544", "V4438", "V6464", "V8354", "V11608", "V15132"};
    std::string _head_race[8] = {"V181", "V801", "V2828", "V5096", "V6802", "V8723", "V11938", "V16086"};
    std::string _wife_education[8] = {"V246", "V794", "V2687", "V5075", "V6788", "V8710", "V12401", "V16162"};
    std::string _head_education[8] = {"V313", "V794", "V2823", "V5074", "V6787", "V8709", "V12400", "V16161"};
    std::string _kids[8] = {"V398", "V550", "V2545", "V4439", "V6465", "V8644", "V12209", "V15133"};
    std::string _head_hour_work[8] = {"V47", "V465", "V2439", "V4332", "V6336", "V8228", "V11146", "V14835"};
    std::string _wife_hour_work[8] = {"V53", "V475", "V2449", "V4719", "V6348", "V8238", "V11252", "V14865"};

    Data_vect entire_data;

    for(int i=0;i<8;i++){
        std::ifstream file(filenames[i]);
        if (!file.is_open()) {
            std::cerr << "Oops, couldn't open file : " << filenames[i] << std::endl;
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
            double afdc = std::stod(row[collumn[_afdc[i]]]); //https://www.geeksforgeeks.org/cpp/cpp-program-for-string-to-double-conversion/ 
            double head_sex = std::stod(row[collumn[_head_sex[i]]]); 
            double head_age = std::stod(row[collumn[_head_age[i]]]);
            double wife_age = std::stod(row[collumn[_wife_age[i]]]);
            double head_race = std::stod(row[collumn[_head_race[i]]]);
            double wife_education = std::stod(row[collumn[_wife_education[i]]]);
            double head_education = std::stod(row[collumn[_head_education[i]]]);
            double kids = std::stod(row[collumn[_kids[i]]]);
            double head_hour_work = std::stod(row[collumn[_head_hour_work[i]]]);
            double wife_hour_work = std::stod(row[collumn[_wife_hour_work[i]]]);
            int outcome;
            if (head_race==1){
                head_race=1; //white
            } else{
                head_race=2;//black/non-white
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

