#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::string filename = "input";
std::string line;
std::vector<std::vector<char>> map;
std::vector<std::vector<char>> antinode_map;

void generate_antinodes(std::vector<std::vector<char>>& map, std::vector<std::vector<char>>& a_map){
	std::vector<std::vector<int>> ants; //antennae
	while(true){
		char sgn = '#';
		for (int i = 0; i < map.size(); ++i){
			for (int j = 0; j < map[i].size(); ++j){
				if (sgn != '#'){
					if (map[i][j] == sgn){
						ants.push_back({i, j});
						map[i][j] = '.';
					}
				} else if(map[i][j] != '.'){
					sgn = map[i][j];
					ants.push_back({i, j});
					map[i][j] = '.';
				}
			}
		}
		if (sgn == '#'){
			break;
		} else {
			for (std::vector<int> ant : ants){
				for (std::vector<int> bnt : ants){
					if (ant != bnt && 2*bnt[0]-ant[0] >= 0 && 2*bnt[0]-ant[0] < map.size() && 2*bnt[1]-ant[1] >= 0 && 2*bnt[1]-ant[1] < map[0].size()){
						antinode_map[2*bnt[0]-ant[0]][2*bnt[1]-ant[1]] = '#';
					}
				}
			}
		}
		sgn = '#';
		ants = {};
	}
}

int count_antinodes(std::vector<std::vector<char>>& a_map){
	int sum = 0;
	for (std::vector<char> v : a_map){
		for (char c : v){
			if (c == '#'){
				++sum;
			}
		}
	}
	return sum;
}

int main(){
	std::ifstream inputFile(filename);
	if(!inputFile.is_open()){
		std::cerr << "Error opening file: " << filename << std::endl;
		return 1;
	}

	while(getline(inputFile, line)){
		std::vector<char> vec = {};
		map.push_back(vec);
		for (char c : line){
			map.back().push_back(c);
		}
	}
	antinode_map = map;
	generate_antinodes(map, antinode_map);
	std::cout << count_antinodes(antinode_map) << std::endl;
	return 0;
}
