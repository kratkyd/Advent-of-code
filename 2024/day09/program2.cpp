//program ran around 6-8 minutes, needs another solution, I think

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

std::string filename = "input";
std::string line;

long long checksum(std::string& line){
	long long ret = 0;
	std::vector<int> back_list;
	int pos = 0;

	if (line.size()%2 == 0){
		line.pop_back();
	}

	for(int index = 0; index < line.size(); index++){
		std::cout << index << std::endl;
		if (index%2 == 0){
			bool valid = true;
			for (int i : back_list){
				if (index == i){
					valid = false;
				}
			}
			for (int i = 0; i < line[index]-'0'; ++i){
				if(valid){
					ret += pos*index/2;
				}
				++pos;
			}
			
		} else {
			int space = line[index]-'0';
			int temp_pos = pos;
			pos += space;
			for (int i = line.size()-1; i > index; i-=2){	
				if (line[i]-'0' <= space){
					bool valid = true;
					for (int j : back_list){
						if (i == j){
							valid = false;
						}
					}
					if(valid){
						for (int j = 0; j < line[i]-'0'; ++j){
							ret += temp_pos*i/2;
							--space;
							++temp_pos;
						}
						back_list.push_back(i);
					}
				}
			}
		}
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
		std::cout << line.size() << std::endl;
		std::cout << checksum(line) << std::endl;
	}
}
