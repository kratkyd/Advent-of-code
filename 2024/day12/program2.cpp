#include <iostream>
#include <string>
#include <fstream>
#include <vector>

std::string filename = "input";
std::string line;
std::vector<std::vector<char>> map;

void print_map(std::vector<std::vector<char>>& map){
    for (std::vector<char> v : map){
        for (char c : v){
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
}

void calculate_fence_per_border(std::vector<std::vector<char>>& map, int i, int j, int& per, int odir=0){
    if (odir == 0){
        while(i>0 && map[i-1][j] == '#'){--i;} 
    }
    int dir = odir;
    int k = i;
    int l = j;
    while(true){
        map[k][l] = '*';  
        if (dir==0){
            if (l==0 || (map[k][l-1]!='#' && map[k][l-1]!='*')){dir=1; ++per;}
            else if (l>0 && k>0 && (map[k-1][l-1]=='#' || map[k-1][l-1]=='*')){--k; --l; dir=3; ++per;}
            else {--l;}
        } else if (dir==1){
            if (k==map.size()-1 || (map[k+1][l]!='#' && map[k+1][l]!='*')){dir=2; ++per;}
            else if (k<map.size()-1 && l>0 && (map[k+1][l-1]=='#' || map[k+1][l-1]=='*')){++k; --l; dir=0; ++per;}
            else {++k;}
        } else if (dir==2){
            if (l==map[k].size()-1 || (map[k][l+1]!='#' && map[k][l+1]!='*')){dir=3; ++per;}
            else if (l<map[k].size()-1 && k<map.size()-1 && (map[k+1][l+1]=='#' || map[k+1][l+1]=='*')){++k; ++l; dir=1; ++per;}
            else {++l;}
        } else if (dir==3){
            if (k==0 || (map[k-1][l]!='#' && map[k-1][l]!='*')){dir=0; ++per;}
            else if (k>0 && l<map[k].size()-1 && (map[k-1][l+1]=='#' || map[k-1][l+1]=='*')){--k; ++l; dir=2; ++per;}
            else {--k;}
        }
        if (k==i && l==j && dir==odir){
            break;
        }
    }
}

void calculate_fence_area(std::vector<std::vector<char>>& map, int i, int j, int& area, char plant){
    ++area;
    map[i][j] = '#';
    if (i>0 && map[i-1][j]==plant){calculate_fence_area(map, i-1, j, area, plant);}
    if (i<map.size()-1 && map[i+1][j]==plant){calculate_fence_area(map, i+1, j, area, plant);}
    if (j>0 && map[i][j-1]==plant){calculate_fence_area(map, i, j-1, area, plant);}
    if (j<map[i].size()-1 && map[i][j+1]==plant){calculate_fence_area(map, i, j+1, area, plant);}
}

void find_enclaves(std::vector<std::vector<char>>& map, int& per){
    for (int i=0; i<map.size(); ++i){
        for (int j=0; j<map[i].size(); ++j){
            if (map[i][j] == '#'){
                if (i>0 && map[i-1][j]!='#' && map[i-1][j]!='*'){calculate_fence_per_border(map, i, j, per, 0);}
                if (j>0 && map[i][j-1]!='#' && map[i][j-1]!='*'){calculate_fence_per_border(map, i, j, per, 1);}
                if (i<map.size()-1 && map[i+1][j]!='#' && map[i+1][j]!='*'){calculate_fence_per_border(map, i, j, per, 2);}
                if (j<map[i].size()-1 && map[i][j+1]!='#' && map[i][j+1]!='*'){calculate_fence_per_border(map, i, j, per, 3);}
            }    
        }
    }
}

void fix_map(std::vector<std::vector<char>>& map){
    for (std::vector<char>& v : map){
        for (char& c : v){
            if (c=='#' || c=='*'){
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
                    calculate_fence_area(map, i, j, area, map[i][j]);
                    calculate_fence_per_border(map, i, j, per);
                    //print_map(map);
                    find_enclaves(map, per);
                    fix_map(map);
                    ret += area*per;
                    //std::cout << ret << std::endl;
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