#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::string filename = "input";
std::string line;
std::vector<std::vector<int>> map;

int test_trailhead(std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& ends, int i, int j){
	int ret = 0;
	int val = map[i][j];
	if (val == 9){
		bool valid = true;
		for (std::vector<int> v : ends){
			if (v[0] == i && v[1] == j){
				valid = false;
			}
		}
		if (valid){
			ends.push_back({i, j});
			return 1;
		} else {
			return 0;
		}
	} else {
		if (i > 0 && map[i-1][j] == val+1){
			ret += test_trailhead(map, ends, i-1, j);
		}
		if (i < map.size()-1 && map[i+1][j] == val+1){
			ret += test_trailhead(map, ends, i+1, j);
		}
		if (j > 0 && map[i][j-1] == val+1){
			ret += test_trailhead(map, ends, i, j-1);
		}
		if (j < map[i].size() && map[i][j+1] == val+1){
			ret += test_trailhead(map, ends, i, j+1);
		}
	}
	return ret;
}

int main(){
	std::ifstream inputFile(filename);
	if (!inputFile.is_open()){
		std::cerr << "Error opening file: " << filename << std::endl;
		return 1;
	}

	while(getline(inputFile, line)){
		std::vector<int> vec;
		for (char c : line){
			vec.push_back(c-'0');
		}
		map.push_back(vec);
	}
	
	int sum = 0;
	for (int i = 0; i < map.size(); ++i){
		for (int j = 0; j < map.size(); ++j){
			if (map[i][j] == 0){
				std::vector<std::vector<int>> ends;
				int val = test_trailhead(map, ends, i, j);
				sum += val;
			}
		}
	}
	std::cout << sum << std::endl;

	return 0;
}
