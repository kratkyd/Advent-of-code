#include <iostream>
#include <string>
#include <fstream>
#include <vector>

std::string filename = "input";
std::string line;
std::vector<std::vector<char>> map;

void calculate_fence(std::vector<std::vector<char>>& map, int i, int j, int& area, int& per, char plant){
    ++area;
    map[i][j] = '#';
    if (i>0){
        if (map[i-1][j]==plant){calculate_fence(map, i-1, j, area, per, plant);}
            else if (map[i-1][j] != '#'){++per;} 
    } else {++per;}
    if (i<map.size()-1){
        if (map[i+1][j]==plant){calculate_fence(map, i+1, j, area, per, plant);}
        else if (map[i+1][j] != '#') {++per;}
    } else {++per;}
    if (j>0){
        if (map[i][j-1]==plant){calculate_fence(map, i, j-1, area, per, plant);}
        else if (map[i][j-1] != '#') {++per;}
    } else {++per;}
    if (j<map[i].size()-1){
        if (map[i][j+1]==plant){calculate_fence(map, i, j+1, area, per, plant);}
        else if (map[i][j+1] != '#') {++per;}
    } else {++per;}
}

void fix_map(std::vector<std::vector<char>>& map){
    for (std::vector<char>& v : map){
        for (char& c : v){
            if (c == '#'){
                c = '.';
            }
        }
    }
}

int fence(std::vector<std::vector<char>>& map){
    bool map_empty = false;
    int ret = 0;
    while(!map_empty){
        map_empty = true;
        for (int i = 0; i < map.size(); ++i){
            for (int j = 0; j < map[i].size(); ++j){
                if (map[i][j]!='.'){
                    int area = 0;
                    int per = 0;
                    calculate_fence(map, i, j, area, per, map[i][j]);
                    ret += area*per;
                    fix_map(map);
                    map_empty = false;
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
    
    while(getline(inputFile, line)){
        std::vector<char> vec;
        for (char c : line){
            vec.push_back(c);
        }
        map.push_back(vec);
    }
    std::cout << fence(map) << std::endl;

    return 0;
}