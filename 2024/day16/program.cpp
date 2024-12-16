//the only thing breaking this one is the  >^> setup, or numbers 4009, 3010, 4011, that is what the "preval" value is for

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::string filename = "input";
std::string line;
std::vector<std::vector<char>> map_char;
std::vector<std::vector<int>> map_num;

void print_map(std::vector<std::vector<int>> map_num){
    for (std::vector<int> v : map_num){
        for (int j = 0;  j < v.size(); ++j){
            if (v[j] == 0){std::cout << ". ";}
            else if (v[j] == -1){std::cout << "r ";}
            else if (v[j] == -2){std::cout << "# ";}
            else if (v[j] == -3){std::cout << "E ";}
            else if (v[j] == -4){std::cout << "O ";}
            else {std::cout << "x ";}
        }
        std::cout << "\n";
    }
    std::cout << "\n\n\n";
}

std::vector<std::vector<int>> configure_map(std::vector<std::vector<char>> map, int& y, int& x, int& ey, int& ex){
    std::vector<std::vector<int>> map_num;
    for (int i = 0; i < map.size(); ++i){
        std::vector<int> vec;
        for (int j = 0; j < map[i].size(); ++j){
            if (map[i][j] == '#'){vec.push_back(-2);}
            else if (map[i][j] == '.'){vec.push_back(0);}
            else if (map[i][j] == 'S'){vec.push_back(-1); y=i; x=j;}
            else if (map[i][j] == 'E'){vec.push_back(-3); ey=i; ex=j;}
            else {std::cout << "Something weird on the map" << "\n";}
        }
        map_num.push_back(vec);
    }
    return map_num;
}

void find_path(std::vector<std::vector<int>>& map, int y, int x, int dir, int n, int& min){
    //print_map(map);
    if (map[y][x] == -3){
        if (min == 0 || min > n){min = n;}
        return;
    }
    map[y][x] = n;
    if (dir==0 && (map[y-1][x]>n+1 || map[y-1][x]==0 || map[y-1][x]==-3)){find_path(map, y-1, x, 0, n+1, min);}
    if ((dir==1 || dir==3) && (map[y-1][x]>n+1000 || map[y-1][x]==0 || map[y-1][x]==-3)){find_path(map, y-1, x, 0, n+1001, min);}

    if (dir==1 && (map[y][x-1]>n+1 || map[y][x-1]==0 || map[y][x-1]==-3)){find_path(map, y, x-1, 1, n+1, min);}
    if ((dir==2 || dir==0) && (map[y][x-1]>n+1000 || map[y][x-1]==0 || map[y][x-1]==-3)){find_path(map, y, x-1, 1, n+1001, min);}

    if (dir==2 && (map[y+1][x]>n+1 || map[y+1][x]==0 || map[y+1][x]==-3)){find_path(map, y+1, x, 2, n+1, min);}
    if ((dir==3 || dir==1) && (map[y+1][x]>n+1000 || map[y+1][x]==0 || map[y+1][x]==-3)){find_path(map, y+1, x, 2, n+1001,min);}

    if (dir==3 && (map[y][x+1]>n+1 || map[y][x+1]==0 || map[y][x+1]==-3)){find_path(map, y, x+1, 3, n+1, min);}
    if ((dir==0 || dir==2) && (map[y][x+1]>n+1000 || map[y][x+1]==0 || map[y][x+1]==-3)){find_path(map, y, x+1, 3, n+1001, min);}
}

int find_path_back(std::vector<std::vector<int>>& map, int y, int x, int preval){
    int ret = 0;
    int val = map[y][x];
    //std::cout << val << " " << map[y][x-1] << std::endl;
    //print_map(map);
    if (map[y-1][x]==val-1 || map[y-1][x]==val-1001 || (map[y-1][x]==val+999 && preval==val+1001)){
        map[y][x]=-4; ret += 1+find_path_back(map, y-1, x, val);
    }
    if (map[y][x-1]==val-1 || map[y][x-1]==val-1001 || (map[y][x-1]==val+999 && preval==val+1001)){
        map[y][x]=-4; ret += 1+find_path_back(map, y, x-1, val);
    }
    if (map[y+1][x]==val-1 || map[y+1][x]==val-1001 || (map[y+1][x]==val+999 && preval==val+1001)){
        map[y][x]=-4; ret += 1+find_path_back(map, y+1, x, val);
    }
    if (map[y][x+1]==val-1 || map[y][x+1]==val-1001 || (map[y][x+1]==val+999 && preval==val+1001)){
        map[y][x]=-4; ret += 1+find_path_back(map, y, x+1, val);
    }
    return ret;
}

int main(){
    std::ifstream inputFile(filename);
    if(!inputFile.is_open()){
        std::cerr << "Error opening file: " << filename << "\n";
        return 1;
    }
    while(getline(inputFile, line)){
        std::vector<char> vec;
        for (char c : line){vec.push_back(c);}
        map_char.push_back(vec);
    }
    int y=0, x=0, ey=0, ex=0, min=0;
    map_num = configure_map(map_char, y, x, ey, ex);
    find_path(map_num, y, x, 3, 0, min);
    std::cout << "First answer: " << min << "\n";
    map_num[ey][ex]=min;
    std::cout << "Second answer: " << find_path_back(map_num, ey, ex, 0)+1 << std::endl;
    return 0;
}