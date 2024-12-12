#include <iostream>
#include <string>
#include <fstream>
#include <regex>

std::string filename = "input1";
std::string line;

int main(){
	std::ifstream inputFile(filename);
	if (!inputFile.is_open()){
		std::cerr << "Error opening file: " << filename << std::endl;
		return 1;
	}

	std::regex mul_regex(R"(mul\(\d+,\d+\)|do\(\)|don't\(\))");
	int sum = 0;	
	bool mul_do = true;

	while(getline(inputFile, line)){
		auto mul_begin = std::sregex_iterator(line.begin(), line.end(), mul_regex);
		auto mul_end = std::sregex_iterator();

		for(std::sregex_iterator i = mul_begin; i != mul_end; ++i){
			std::smatch match = *i;
			std::string match_str = match.str();
			if (match_str == "do()"){
				mul_do = true;
			} else if (match_str == "don't()"){
				mul_do = false;
			} else if (mul_do) {
				std::regex num_regex(R"(\d+)");
				auto num_it = std::sregex_iterator(match_str.begin(), match_str.end(), num_regex);
				std::string first_str = (*num_it).str();
				num_it++;
				std::string second_str = (*num_it).str();
				sum += stoi(first_str)*stoi(second_str);
			}
		}
	}
	
	std::cout << sum << std::endl;
	return 0;
}
