#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::string filename = "input";
std::string line;
std::string instructions;
std::vector<std::vector<char>> map;

void print_map(std::vector<std::vector<char>> map){
    for (std::vector<char> v : map){
        for (char c : v){std::cout << c << " ";}
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

void find_position(std::vector<std::vector<char>> map, int& x, int& y){
    for (int i=0; i<map.size(); ++i){
        for (int j=0; j<map[i].size(); ++j){
            if (map[i][j] == '@'){
                y = i;
                x = j;
                return;
            }
        }
    }
}

void follow_instructions(std::vector<std::vector<char>>& map, std::string instructions){
    int x, y;
    find_position(map, x, y);
    for (char dir : instructions){
        if (dir == '^'){
            if (map[y-1][x] == '.'){
                map[y][x] = '.';
                map[y-1][x] = '@';
                --y;
            } else {
                int lx=x, ly=y-1;
                while(map[ly][lx] == 'O'){--ly;}
                if (map[ly][lx] == '#'){continue;}
                else if (map[ly][lx] == '.'){
                    while(map[ly][lx] != '@'){
                        map[ly][lx]=map[ly+1][lx];
                        ++ly;
                    }
                    map[ly][lx]='.';
                    --y;
                } else {std::cerr << "Undefined object on map: " << map[ly][lx] <<  std::endl;}
            }
        } else if (dir == '>'){
            if (map[y][x+1] == '.'){
                map[y][x] = '.';
                map[y][x+1] = '@';
                ++x;
            } else {
                int lx=x+1, ly=y;
                while(map[ly][lx] == 'O'){++lx;}
                if(map[ly][lx] == '#'){continue;}
                else if (map[ly][lx] == '.'){  
                    while(map[ly][lx] != '@'){
                        map[ly][lx]=map[ly][lx-1];
                        --lx;
                    }
                    map[ly][lx]='.';
                    ++x;
                } else {std::cerr << "Undefined object on map: " << map[ly][lx] << std::endl;}
            }
        } else if (dir == 'v'){
            if (map[y+1][x] == '.'){
                map[y][x] = '.';
                map[y+1][x] = '@';
                ++y;
            } else {
                int lx=x, ly=y+1;
                while(map[ly][lx] == 'O'){++ly;}
                if(map[ly][lx]=='#'){continue;}
                else if (map[ly][lx] == '.'){
                    while(map[ly][lx] != '@'){
                        map[ly][lx]=map[ly-1][lx];
                        --ly;
                    }
                    map[ly][lx]='.';
                    ++y;
                } else {std::cerr << "Undefined object on map: " << map[ly][lx] << std::endl;}
            }
        } else if (dir == '<'){
            if (map[y][x-1] == '.'){
                map[y][x] = '.';
                map[y][x-1] = '@';
                --x;
            } else {
                int lx=x-1, ly=y;
                while(map[ly][lx] == 'O'){--lx;}
                if(map[ly][lx]=='#'){continue;}
                else if (map[ly][lx] == '.'){
                    while(map[ly][lx] != '@'){
                        map[ly][lx]=map[ly][lx+1];
                        ++lx;
                    }
                    map[ly][lx]='.';
                    --x;
                } else {std::cerr << "Undefined object on map: " << map[ly][lx] << std::endl;}
            }
        }
    }
}

int calculate_gps(std::vector<std::vector<char>> map){
    int ret = 0;
    for (int i=0; i<map.size(); ++i){
        for (int j=0; j<map[i].size(); ++j){
            if (map[i][j] == 'O'){ret += 100*i+j;}
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
        if (line.size() != 0){
            std::vector<char> vec;
            for (char c : line){vec.push_back(c);}
            map.push_back(vec);
        } else {break;}
    }
    while(getline(inputFile, line)){
       instructions.append(line); 
    }
    follow_instructions(map, instructions);
    std::cout << calculate_gps(map) << std::endl;
    return 0;
}