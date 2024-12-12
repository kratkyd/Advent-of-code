#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

std::vector<int> list1, list2;
std::string filename = "input1";
std::string line;

int main(){
	std::ifstream inputFile(filename);
	if (!inputFile.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return 1;
	}	


	while(getline(inputFile, line)) {
		list1.push_back(stoi(line.substr(0, line.find("   "))));
		line.erase(0, line.find("   ")+3); 
		list2.push_back(stoi(line));
	}

	std::sort(list1.begin(), list1.end());
	std::sort(list2.begin(), list2.end());

	int sum = 0;
	for (int i = 0; i < list1.size(); ++i){
		sum += abs(list1[i]-list2[i]);
	}	
	std::cout << "First answer: " << sum << std::endl;

	int sim_val=0, k=0, l=0, num=0, rep=0;
	while (k < list1.size()){
		rep = 0;
		num = list1[k];
		while(l < list2.size() && list2[l] < num){
			++l;
		}
		if(list2[l] == num) {
			while(list2[l] == num){
				++rep;
				++l;
			}
		}
		sim_val += rep*num;
		++k;
	}
	
	std::cout << "Second answer: " << sim_val << std::endl;		

	inputFile.close();
	return 0;
}
