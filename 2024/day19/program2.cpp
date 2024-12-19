//Third time this year I needed a hint, and it's the same thing as the first one, memoization, I have to remember that
//Not with the implementation of the memoization, that I did myself, just the idea of using one

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

std::string filename = "input";
std::string line;
std::vector<std::string> patterns;

long long test_line(std::string line, std::vector<std::string> patterns, std::vector<long long>& memo, int ind = 0){
    long long ret = 0;
    if (ind >= line.size()){return 1;}
    if (memo[ind] != 0){return memo[ind];}
    for (std::string p : patterns){
        bool fits = true;
        if (ind+p.size()<=line.size()){
            for (int i = 0; i < p.size(); ++i){
                if (line[ind+i] != p[i]){fits = false; break;}
            }
        } else {fits = false;}
        if (fits){ret += test_line(line, patterns, memo, ind+p.size());}
    }
    if (memo[ind]==0){memo[ind]=ret;}
    return ret;
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
    long long sum = 0;
    while(getline(inputFile, line)){
        std::vector<long long> memo(patterns.size(), 0);
        //std::cout << line << "\n";
        sum += test_line(line, patterns, memo);
    }
    std::cout << sum << "\n";
    return 0;
}