#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>

std::string filename = "input";
std::string line;

bool eval(long long& target, std::vector<long long>& vals, long long temp = 0, int index = 0){
	if(index == vals.size()-1){
		return (temp+vals[index] == target || temp*vals[index] == target);
	} else {
		return (eval(target, vals, temp+vals[index], index+1) || eval(target, vals, temp*vals[index], index+1));
	}
}

int main(){
	std::ifstream inputFile(filename);
	if(!inputFile.is_open()){
		std::cerr << "Error opening file: " << filename << std::endl;
		return 1;
	}
	
	long long sum = 0;
	while(getline(inputFile, line)){
		std::vector<long long> vals;
		std::regex num_regex(R"(\d+)");
		auto nums_begin = std::sregex_iterator(line.begin(), line.end(), num_regex);
		auto nums_end = std::sregex_iterator();


		long long target = stoll((*nums_begin).str());
		nums_begin++;

		for (std::sregex_iterator i = nums_begin; i != nums_end; ++i){
			vals.push_back(stoi((*i).str()));
		}
		if(eval(target, vals)){
			sum += target;
		}
	} 
	std::cout << sum << std::endl;
}
