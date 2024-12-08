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
		for (int j = 0; j < lines[i].size(); ++j){
			if (lines[i][j] == 'A' && i>0 && i<lines.size()-1 && j>0 && j<lines[i].size()-1){
				if ((lines[i-1][j-1]=='M' && lines[i+1][j+1]=='S' || lines[i+1][j+1]=='M' && lines[i-1][j-1]=='S') && (lines[i-1][j+1]=='M' && lines[i+1][j-1]=='S' || lines[i+1][j-1]=='M' && lines[i-1][j+1]=='S')){
					sum++;
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
