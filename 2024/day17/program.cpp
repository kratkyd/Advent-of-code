//My favourite one so far, interesting puzzle

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <cmath>

//int A=729, B=0, C=0;
//std::vector<int> inst = {0, 1, 5, 4, 3, 0};
//std::vector<int> inst = {0, 3, 5, 4, 3, 0};

unsigned long long A=64196994, B=0, C=0;
std::vector<unsigned int> inst = {2, 4, 1, 1, 7, 5, 1, 5, 4, 0, 0, 3, 5, 5, 3, 0};


std::vector<unsigned int> outs;

unsigned long long combo(unsigned int op, unsigned long long A, unsigned long long B, unsigned long long C){
    if (op == 0 || op == 1 || op == 2 || op == 3){return op;}
    else if (op == 4){return A;}
    else if (op == 5){return B;}
    else if (op == 6){return C;}
    std::cerr << "Unknown value: " << op << "\n";
    return 0;
}

std::vector<unsigned int> eval(std::vector<unsigned int> inst, unsigned long long&A, unsigned long long&B, unsigned long long&C){
    std::vector<unsigned int> ret;
    for (int i = 0; i < inst.size()-1; i+=2){
        if (inst[i]==0){A = A/pow(2, combo(inst[i+1], A, B, C));}
        else if (inst[i]==1){B = B^inst[i+1];}
        else if (inst[i]==2){B = combo(inst[i+1], A, B, C)%8;}
        else if (inst[i]==3 && A!=0){i = inst[i+1]-2;}
        else if (inst[i]==4){B = B^C;}
        else if (inst[i]==5){ret.push_back(combo(inst[i+1], A, B, C)%8);}
        else if (inst[i]==6){B = A/pow(2, combo(inst[i+1], A, B, C));}
        else if (inst[i]==7){C = A/pow(2, combo(inst[i+1], A, B, C));}
    }
    return ret;
}

unsigned long long find_the_num(std::vector<unsigned int> inst, int i, unsigned long long A){
    if (i<0){return A;}
    A*=8;
    for (int j = 0; j < 8; ++j){
        unsigned long long x = A+j;
        if (((((x%8)^1)^5)^(unsigned long long)(x/(pow(2, (x%8)^1))))%8==inst[i]){
            if (find_the_num(inst, i-1, x)!=0){return find_the_num(inst, i-1, x);}
        }
    }
    return 0;
}

int main(){
    outs = eval(inst, A, B, C);
    std::cout << "First answer: ";
    for (int i = 0; i < outs.size()-1; ++i){
        std::cout << outs[i] << ",";
    }
    std::cout << outs[outs.size()-1] << "\n";
    std::cout << "Second answer: " << find_the_num(inst, inst.size()-1, 0) << "\n";

    return 0;
}