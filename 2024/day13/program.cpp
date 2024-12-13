#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <cmath>

std::string filename = "input";
std::string line;

bool is_whole(long double num){
    long double eps = 0.01;
    return (fabsl(num-floorl(num))<=eps);
}

long long get_prize(long double ax, long double ay, long double bx, long double by, long double x, long double y){
    if (ay*bx-ax*by == 0){
        std::cout << "it happened" << std::endl;
        return 0;
        //the code is technically wrong, but the situation that would break it didn't occur in the run, so I just didn't do it
    }
    long double a = (y*bx-x*by)/(ay*bx-ax*by);
    //printf("%Lf\n", a);
    long double b = (x-ax*a)/bx;
    //std::cout << b << ": " << is_whole(b) << "\n";
    if(is_whole(a) && is_whole(b)){
        return 3*a+b;
    }
    return 0;
}

int main(){
    std::ifstream inputFile(filename);

    if(!inputFile.is_open()){
        std::cerr << "Error opening file: " << filename << std::endl;   
        return 1;
    }
    long long ax, bx, ay, by, x, y, sum1=0, sum2=0;
    while(getline(inputFile, line)){
        std::regex nums_regex(R"(\d+)");
        auto nums = std::sregex_iterator(line.begin(), line.end(), nums_regex);
        ax = stoll((*nums++).str());
        ay = stoll((*nums).str());
        getline(inputFile, line);
        nums = std::sregex_iterator(line.begin(), line.end(), nums_regex); 
        bx = stoll((*nums++).str());
        by = stoll((*nums).str());
        getline(inputFile, line);
        nums = std::sregex_iterator(line.begin(), line.end(), nums_regex); 
        x = stoll((*nums++).str());
        y = stoll((*nums).str());
        getline(inputFile, line);
        sum1 += get_prize(ax, ay, bx, by, x, y);
        sum2 += get_prize(ax, ay, bx, by, x+10000000000000, y+10000000000000);
    }
    std::cout << "First answer: " << sum1 << "\n";
    std::cout << "Second answer: " << sum2 << "\n";
    //std::cout << get_prize(26, 66, 67, 21, 10000000012748, 10000000012176);
    return 0;
}