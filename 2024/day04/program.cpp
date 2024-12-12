#include <iostream>
#include <string>
#include <fstream>
#include <vector>


std::string filename = "input1";
std::string line;
std::vector<std::string> lines;

int check_lines(std::vector<std::string> lines){
	int sum = 0;
	for (int i = 0; i < lines.size(); ++i){
		std::cout << "i: " << i << std::endl;
		for (int j = 0; j < lines[i].size(); ++j){
			std::cout << "j: " << j << std::endl;
			if (lines[i][j] == 'X'){
				if (i>2){
					if(lines[i-1][j]=='M' && lines[i-2][j]=='A' && lines[i-3][j]=='S'){
						++sum;
					}
					if(j>2 && lines[i-1][j-1]=='M' && lines[i-2][j-2]=='A' && lines[i-3][j-3]=='S'){
						++sum;
					}
					if(j<lines[i].size()-3 && lines[i-1][j+1]=='M' && lines[i-2][j+2]=='A' && lines[i-3][j+3]=='S'){
						++sum;
					}
				}
				if (j>2 && lines[i][j-1]=='M' && lines[i][j-2]=='A' && lines[i][j-3]=='S'){
					++sum;
				}
				if (j<lines[i].size()-3 && lines[i][j+1]=='M' && lines[i][j+2]=='A' && lines[i][j+3]=='S'){
					++sum;
				}
				if (i<lines.size()-3){
					if(lines[i+1][j]=='M' && lines[i+2][j]=='A' && lines[i+3][j]=='S'){
						++sum;
					}
					if(j>2 && lines[i+1][j-1]=='M' && lines[i+2][j-2]=='A' && lines[i+3][j-3]=='S'){
						++sum;
					}
					if(j<lines[i].size()-3 && lines[i+1][j+1]=='M' && lines[i+2][j+2]=='A' && lines[i+3][j+3]=='S'){
						++sum;
					}
				}
			}
		}
	}
	return sum;
}

int main(){
	std::ifstream inputFile(filename);
	if (!inputFile.is_open()){
		std::cerr << "Error opening file: " << filename << std::endl;
		return 1;
	}
	while(getline(inputFile, line)){
		lines.push_back(line);
	}
	
	std::cout << check_lines(lines) << std::endl;

	return 0;
}
