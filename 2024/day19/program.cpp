#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

std::string filename = "input";
std::string line;
std::vector<std::string> patterns;

int test_line(std::string line, std::vector<std::string> patterns){
    if (line.size() == 0){return 1;}
    for (std::string p : patterns){
        bool fits = true;
        if (line.size()>=p.size()){
            for (int i = 0; i < p.size(); ++i){
                if (line[i] != p[i]){fits = false; break;}
            }
        } else {fits = false;}
        if (fits){
            std::string newline = line;
            newline.erase(newline.begin(), newline.begin()+p.size());
            int ret = test_line(newline, patterns);
            if (ret == 1){return 1;}
        }
    }
    return 0;
}

int main(){
    std::ifstream inputFile(filename);
    if(!inputFile.is_open()){
        std::cerr << "Error opening file: " << filename << "\n";
        return 1;
    }
    getline(inputFile, line);
    std::regex letters_regex(R"([a-z]+)");
    auto letters_begin = std::sregex_iterator(line.begin(), line.end(), letters_regex);
    auto letters_end = std::sregex_iterator();
    for (std::sregex_iterator it = letters_begin; it != letters_end; ++it){
        patterns.push_back((*it).str());
    }
    getline(inputFile, line);
    int sum = 0;
    while(getline(inputFile, line)){
        std::cout << line << "\n";
        sum += test_line(line, patterns);
    }
    std::cout << sum << "\n";
    return 0;
}