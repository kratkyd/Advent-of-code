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

bool step(std::vector<std::vector<char>>& map, std::vector<int>& guard_pos, int& sum, char& prev){
	char guard = map[guard_pos[0]][guard_pos[1]];
	if (prev == 'u'){
		map[guard_pos[0]][guard_pos[1]] = '.';
	} else if (prev == '.'){
		map[guard_pos[0]][guard_pos[1]] = '3';
	} else if (prev == '3'){
		map[guard_pos[0]][guard_pos[1]] = '2';
	} else if (prev == '2'){
		map[guard_pos[0]][guard_pos[1]] = '1';
	} else if (prev == '1'){
		map[guard_pos[0]][guard_pos[1]] = '0';
	} else if (prev == '0'){
		sum++;
		return false;
	} else {
		std::cerr << "Error: stepped into something vile" << std::endl;
		return false;
	}
	if (guard == '^'){
		if (guard_pos[0]==0){
			return false;
		} else if (map[guard_pos[0]-1][guard_pos[1]] == '#'){
			map[guard_pos[0]][guard_pos[1]] = '>';
		} else {
			prev = map[guard_pos[0]-1][guard_pos[1]];
			map[guard_pos[0]-1][guard_pos[1]] = '^';
			guard_pos[0] -= 1;
		}
	} else if (guard == '>'){
		if (guard_pos[1]==map[0].size()-1){
			return false;
		} else if (map[guard_pos[0]][guard_pos[1]+1] == '#'){
			map[guard_pos[0]][guard_pos[1]] = 'v';
		} else{
			prev = map[guard_pos[0]][guard_pos[1]+1];
			map[guard_pos[0]][guard_pos[1]+1] = '>';
			guard_pos[1] += 1;
		}
	} else if (guard == 'v'){
		if (guard_pos[0]==map.size()-1){
			return false;
		} else if (map[guard_pos[0]+1][guard_pos[1]] == '#'){
			map[guard_pos[0]][guard_pos[1]] = '<';
		} else{
			prev = map[guard_pos[0]+1][guard_pos[1]];
			map[guard_pos[0]+1][guard_pos[1]] = 'v';
			guard_pos[0] += 1;
		}
	} else if (guard == '<'){
		if (guard_pos[1]==0){
			return false;
		} else if (map[guard_pos[0]][guard_pos[1]-1] == '#'){
			map[guard_pos[0]][guard_pos[1]] = '^';
		} else {
			prev = map[guard_pos[0]][guard_pos[1]-1];
			map[guard_pos[0]][guard_pos[1]-1] = '<';
			guard_pos[1] -= 1;
		}
	} else {
		std::cerr << "Error while stepping: " << guard << std::endl;
		std::cout << guard_pos[0] << " " << guard_pos[1] << std::endl;
		return false;
	}
	return true;
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
	std::vector<int> start_guard_pos = char_pos(map);
	std::vector<int> guard_pos = start_guard_pos;
	int sum = 0;

	for (int i = 0; i < map.size(); ++i){
		for (int j = 0; j < map[i].size(); ++j){
			if (start_guard_pos[0] != i || start_guard_pos[1] != j){
				char prev = 'u';
				guard_pos = start_guard_pos;
				std::vector<std::vector<char>> map2 = map;
				map2[i][j] = '#';
				while(step(map2, guard_pos, sum, prev));
			}	
		}
	}
	std::cout << sum << std::endl;
}
