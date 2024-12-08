#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::string filename = "input";
std::string line;
std::vector<std::vector<char>> map;

void print_map(){
	for(std::vector<char> v : map){
		for(char c : v){
			std::cout << c << " ";
		}
		std::cout << std::endl;
	}
}

std::vector<int> char_pos(std::vector<std::vector<char>> map){
	for(int i = 0; i < map.size(); ++i){
		for(int j = 0; j < map[i].size(); ++j){
			if (map[i][j] == '^' || map[i][j] == '>' || map[i][j] == 'v'  || map[i][j] == '<'){
				return std::vector<int>{i, j};
			}
		}
	}
	std::cerr << "Couldn't find guard" << std::endl;
	return std::vector<int>{-1, -1};
}

bool step(std::vector<std::vector<char>>& map, std::vector<int>& guard_pos){
	char guard = map[guard_pos[0]][guard_pos[1]];
	map[guard_pos[0]][guard_pos[1]] = 'X';
	if (guard == '^'){
		if (guard_pos[0]==0){
			return false;
		} else if (map[guard_pos[0]-1][guard_pos[1]] == '#'){
			map[guard_pos[0]][guard_pos[1]] = '>';
		} else {
			map[guard_pos[0]-1][guard_pos[1]] = '^';
			guard_pos[0] -= 1;
		}
	} else if (guard == '>'){
		if (guard_pos[1]==map[0].size()-1){
			return false;
		} else if (map[guard_pos[0]][guard_pos[1]+1] == '#'){
			map[guard_pos[0]][guard_pos[1]] = 'v';
		} else{
			map[guard_pos[0]][guard_pos[1]+1] = '>';
			guard_pos[1] += 1;
		}
	} else if (guard == 'v'){
		if (guard_pos[0]==map.size()-1){
			return false;
		} else if (map[guard_pos[0]+1][guard_pos[1]] == '#'){
			map[guard_pos[0]][guard_pos[1]] = '<';
		} else{
			map[guard_pos[0]+1][guard_pos[1]] = 'v';
			guard_pos[0] += 1;
		}
	} else if (guard == '<'){
		if (guard_pos[1]==0){
			return false;
		} else if (map[guard_pos[0]][guard_pos[1]-1] == '#'){
			map[guard_pos[0]][guard_pos[1]] = '^';
		} else {
			map[guard_pos[0]][guard_pos[1]-1] = '<';
			guard_pos[1] -= 1;
		}
	} else {
		std::cerr << "Error while stepping" << std::endl;
		return false;
	}
	return true;
}

int count_crosses(std::vector<std::vector<char>> map){
	int sum = 0;
	for (std::vector<char> v : map){
		for (char c : v){
			if (c == 'X'){
				++sum;
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
		std::vector<char> vec = {};
		map.push_back(vec);
		for (char c : line){
			map.back().push_back(c);
		}
	}

	std::vector<int> guard_pos = char_pos(map);
	while(step(map, guard_pos));
	std::cout << count_crosses(map) << std::endl;
}
