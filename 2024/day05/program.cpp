#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::string filename = "input1";
std::string line;
std::vector<int> rulesA;
std::vector<int> rulesB;
std::vector<std::vector<int>> pages;

void print_vector(std::vector<int> vec){
	for (int i : vec){
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

int test_page(std::vector<int> page, std::vector<int> rulesA, std::vector<int> rulesB){
	int sum = 0;
	for (int i = 1; i < page.size(); ++i){
		for (int v = 0; v < rulesB.size(); ++v){
			if (rulesA[v] == page[i]){
				for (int j = 0; j < i; ++j){
					if (rulesB[v] == page[j]){
						return 0;
					}
				}
			}
		}
	}
	return page[page.size()/2];
}

int test_page2(std::vector<int> page, std::vector<int> rulesA, std::vector<int> rulesB, bool correct = true){
	int sum = 0;
	for (int i = 1; i < page.size(); ++i){
		for (int v = 0; v < rulesB.size(); ++v){
			if (rulesA[v] == page[i]){
				for (int j = 0; j < i; ++j){
					if (rulesB[v] == page[j]){
						int temp = page[i];
						page[i] = page[j];
						page[j] = temp;
						return test_page2(page, rulesA, rulesB, false);
					}
				}
			}
		}
	}
	if (correct){
		return 0;
	} else {
		return page[page.size()/2];
	}
}


int main(){
	std::ifstream inputFile(filename);
	if (!inputFile.is_open()){
		std::cerr << "Error opening file: " << filename << std::endl;
		return 1;
	}
	while(getline(inputFile, line)){
		if (line == ""){
			break;
		}
		rulesA.push_back(stoi(line.substr(0, 2)));
		rulesB.push_back(stoi(line.substr(3, 2)));		
	}

	while(getline(inputFile, line)){
		std::vector<int> line_vec;
		while(line.size() > 2){
			line_vec.push_back(stoi(line.substr(0, 2)));
			line.erase(0, 3);
		}
		line_vec.push_back(stoi(line.substr(0, 2)));
		pages.push_back(line_vec);
	}

	int sum = 0;	
	for (auto page : pages){
		sum += test_page(page, rulesA, rulesB);
	}	

	int sum2 = 0;
	for (auto page : pages){
		sum2 += test_page2(page, rulesA, rulesB);
	}	
	std::cout << "First solution: " <<  sum << std::endl;
	std::cout << "Second solution: " << sum2 << std::endl;
	return 0;
}
