#include <iostream>
#include <string>
#include <fstream>

std::string filename = "input";
std::string line;

long long checksum(std::string& line){
	long long ret = 0;
	int index = 0;
	int pos = 0;
	int back_num;
	int back_num_size=0;
	if (line.size()%2 == 0){
		line.pop_back();
	}
	while(index < line.size()){
		if (index%2 == 0){
			for (int i = 0; i < line[index]-'0'; ++i){
				ret += pos*index/2;
				++pos;
			}
		} else {
			for (int i = 0; i < line[index]-'0'; ++i){
				if (back_num_size == 0){
					if (index != line.size()-1){
						back_num = (line.size()-1)/2;
						back_num_size = line[line.size()-1]-'0';
						line.pop_back();
						if (index != line.size()-1){
							line.pop_back();
						}
					} else{
						break;
					}
				}
				ret += back_num*pos;
				--back_num_size;
				++pos;
			}
		}
		
		++index;
	}
	for (int i = 0; i < back_num_size; ++i){
		ret += back_num*pos;
		++pos;
	}
	return ret;
}

int main(){
	std::ifstream inputFile(filename);
	if(!inputFile.is_open()){
		std::cerr << "Error opening file: " << filename << std::endl;
		return 1;
	}
	
	std::string expanded = "";
	while(getline(inputFile, line)){
		std::cout << checksum(line) << std::endl;
	}
}
