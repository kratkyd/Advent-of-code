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

bool is_pushable_vertical(std::vector<std::vector<char>> map, int i, int j, char dir){
    if (dir == '^'){
        if (map[i-1][j] == '.' && map[i-1][j+1] == '.'){return true;}
        else if (map[i-1][j] == '['){return is_pushable_vertical(map, i-1, j, dir);}
        else if (map[i-1][j] == ']' && map[i-1][j+1] == '.'){return is_pushable_vertical(map, i-1, j-1, dir);}
        else if (map[i-1][j] == '.' && map[i-1][j+1] == '['){return is_pushable_vertical(map, i-1, j+1, dir);}
        else if (map[i-1][j] == ']' && map[i-1][j+1] == '['){
            return (is_pushable_vertical(map, i-1, j-1, dir)&&is_pushable_vertical(map, i-1, j+1, dir));
        } else {return false;}
    } else if (dir == 'v'){
        if (map[i+1][j] == '.' && map[i+1][j+1] == '.'){return true;}
        else if (map[i+1][j] == '['){return is_pushable_vertical(map, i+1, j, dir);}
        else if (map[i+1][j] == ']' && map[i+1][j+1] == '.'){return is_pushable_vertical(map, i+1, j-1, dir);}
        else if (map[i+1][j] == '.' && map[i+1][j+1] == '['){return is_pushable_vertical(map, i+1, j+1, dir);}
        else if (map[i+1][j] == ']' && map[i+1][j+1] == '['){
            return (is_pushable_vertical(map, i+1, j-1, dir)&&is_pushable_vertical(map, i+1, j+1, dir));
        } else {return false;}
    }
}

void push_box_vertical(std::vector<std::vector<char>>& map, int i, int j, char dir){
    if (dir == '^'){
        if (map[i-1][j] == ']'){push_box_vertical(map, i-1, j-1, dir);}
        if (map[i-1][j] == '['){push_box_vertical(map, i-1, j, dir);}
        if (map[i-1][j+1] == '['){push_box_vertical(map, i-1, j+1, dir);}
        if (map[i-1][j] == '.' && map[i-1][j+1] == '.'){
            map[i-1][j] = '[';
            map[i-1][j+1] = ']';
            map[i][j] = '.';
            map[i][j+1] = '.';
        }
    } else if (dir == 'v'){
        if (map[i+1][j] == ']'){push_box_vertical(map, i+1, j-1, dir);}
        if (map[i+1][j] == '['){push_box_vertical(map, i+1, j, dir);}
        if (map[i+1][j+1] == '['){push_box_vertical(map, i+1, j+1, dir);}
        if (map[i+1][j] == '.' && map[i+1][j+1] == '.'){
            map[i+1][j] = '[';
            map[i+1][j+1] = ']';
            map[i][j] = '.';
            map[i][j+1] = '.';
        }
    } 
}

void follow_instructions(std::vector<std::vector<char>>& map, std::string instructions){
    int x, y;
    find_position(map, x, y);
    for (char dir : instructions){
        //std::cout << dir << std::endl;
        //print_map(map);
        if (dir == '^'){
            if (map[y-1][x] == '.'){
                map[y][x] = '.';
                map[y-1][x] = '@';
                --y;
            } else if (map[y-1][x] == '[' && is_pushable_vertical(map, y-1, x, dir)){
                push_box_vertical(map, y-1, x, dir);
                map[y][x] = '.';
                map[y-1][x] = '@';
                --y;
            } else if (map[y-1][x] == ']' && is_pushable_vertical(map, y-1, x-1, dir)){
                push_box_vertical(map, y-1, x-1, dir);
                map[y][x] = '.';
                map[y-1][x] = '@';
                --y;
            }      
        } else if (dir == '>'){
            if (map[y][x+1] == '.'){
                map[y][x] = '.';
                map[y][x+1] = '@';
                ++x;
            } else {
                int lx=x+1, ly=y;
                while(map[ly][lx] == '[' || map[ly][lx] == ']'){++lx;}
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
            } else if (map[y+1][x] == '[' && is_pushable_vertical(map, y+1, x, dir)){
                push_box_vertical(map, y+1, x, dir);
                map[y][x] = '.';
                map[y+1][x] = '@';
                ++y;
            } else if (map[y+1][x] == ']' && is_pushable_vertical(map, y+1, x-1, dir)){
                push_box_vertical(map, y+1, x-1, dir);
                map[y][x] = '.';
                map[y+1][x] = '@';
                ++y;
            }
        } else if (dir == '<'){
            if (map[y][x-1] == '.'){
                map[y][x] = '.';
                map[y][x-1] = '@';
                --x;
            } else {
                int lx=x-1, ly=y;
                while(map[ly][lx] == '[' || map[ly][lx] == ']'){--lx;}
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
            if (map[i][j] == '['){ret += 100*i+j;}
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
            for (char c : line){
                if (c == 'O'){
                    vec.push_back('[');
                    vec.push_back(']');
                } else if (c == '@'){
                    vec.push_back('@');
                    vec.push_back('.');
                } else {
                    vec.push_back(c);
                    vec.push_back(c);
                }
            }
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