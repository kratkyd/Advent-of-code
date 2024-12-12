#include <iostream>
#include <string>
#include <fstream>
#include <vector>

std::string filename = "input1";
std::string line;

void print_vec(std::vector<int> vec){
	for (int i = 0; i < vec.size(); ++i){
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}	

bool test_line(std::string line){
	std::vector<int> vec;
	if(line.size() > 0){
		vec.push_back(stoi(line.substr(0, line.find(" "))));
	}
	while(line.size() > 0){
		line.erase(0, line.find(" ")+1);
		if (line.find(" ") != -1){
			vec.push_back(stoi(line.substr(0, line.find(" "))));
		} else {
			vec.push_back(stoi(line));
			line.erase(0, line.size());
		}
	}
	if(vec.size() == 2){
		if (abs(vec[0]-vec[1])<1 || abs(vec[0]-vec[1])>3){
			return false;
		}
	} else if (vec.size() > 2){
		if (vec[0] == vec[1]){
			return false;
		}
		int sgn = (vec[1]-vec[0])/abs(vec[1]-vec[0]);
		for (int i = 1; i < vec.size(); ++i){
			if ((vec[i]-vec[i-1])*sgn<1 || (vec[i]-vec[i-1])*sgn>3){
				return false;
			}
		}
	}
	return true;
}	
	
bool test_vec(std::vector<int> vec, bool mistake){

	if (vec.size() > 2){
		if (vec[0] == vec[1]){
			if (mistake){
				return false;
			} else {
				std::vector<int> v1 = vec;
				v1.erase(v1.begin());
				std::vector<int> v2 = vec;
				v2.erase(v2.begin()+1);
				return (test_vec(v1, true) || test_vec(v2, true));
			}
		}
		int sgn = (vec[1]-vec[0])/abs(vec[1]-vec[0]);
		for (int i = 1; i < vec.size(); ++i){
			if ((vec[i]-vec[i-1])*sgn<1 || (vec[i]-vec[i-1])*sgn>3){
				if (mistake){
					return false;
				} else {
					std::vector<int> v1 = vec;
					v1.erase(v1.begin()+i-1);
					print_vec(v1);
					std::vector<int> v2 = vec;
					v2.erase(v2.begin()+i);
					print_vec(v2);
					std::vector<int> v3 = vec;
					v3.erase(v3.begin());
					return (test_vec(v1, true) || test_vec(v2, true) || test_vec(v3, true));
				}
			}
		}
	}
	return true;
}

bool test_line2(std::string line){
	std::vector<int> vec;
	
	if(line.size() > 0){
		vec.push_back(stoi(line.substr(0, line.find(" "))));
	}
	
	while(line.size() > 0){
		line.erase(0, line.find(" ")+1);
		if (line.find(" ") != -1){
			vec.push_back(stoi(line.substr(0, line.find(" "))));
		} else {
			vec.push_back(stoi(line));
			line.erase(0, line.size());
		}
	}

	return test_vec(vec, false);

}



int main(){
	std::ifstream inputFile(filename);
	if (!inputFile.is_open()){
		std::cerr << "Error opening file: " << filename << std::endl;
		return 1;
	}
	
	int sum1 = 0;
	int sum2 = 0;
	while(getline(inputFile, line)){
		if(test_line(line)){
			++sum1;
		}
		if(test_line2(line)){
			++sum2;
		} else {
			std::cout << line << std::endl;
		}
	}
	std::cout << "First answer: " << sum1 << std::endl;
	std::cout << "Second answer: " << sum2 << std::endl;

	return 0;
}
