#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::string filename = "input";
std::string line;
std::vector<std::vector<int>> map;
int map_size = 71;
int input_num = 1024;
//int map_size = 71;

void print_map(std::vector<std::vector<int>> map){
    for (std::vector<int> v : map){
        for (int i : v){
            if (i == -1){std::cout << "# ";}
            else if (i == 0){std::cout << ". ";}
            else if (i>0){std::cout << "O ";}
            else {std::cerr << "Unknonw object on the map"<<"\n";}
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void initialize_map(std::vector<std::vector<int>>& map){
    map = {};
    std::vector<int> vec;
    for (int i = 0; i < map_size+2; ++i){vec.push_back(-1);}
    map.push_back(vec);
    for (int i = 0; i < map_size; ++i){
        vec = {-1};
        for (int j = 0; j < map_size; ++j){vec.push_back(0);}
        vec.push_back(-1);
        map.push_back(vec);
    }
    vec = {};
    for (int i = 0; i < map_size+2; ++i){vec.push_back(-1);}
    map.push_back(vec);
}

int find_path(std::vector<std::vector<int>>& map){
    std::vector<std::vector<int>> ends;
    std::vector<std::vector<int>> new_ends = {{1, 1}};
    int n = 1;
    map[1][1] = 1;
    while(true){
        //print_map(map);
        ++n;
        ends = new_ends;
        if (ends.size() == 0){return 0;}
        new_ends = {};
        std::vector<std::vector<int>>::iterator end = ends.begin();
        while (end != ends.end()){
            if ((*end)[0]==map_size && (*end)[1]==map_size){return n-2;}
            if (map[(*end)[0]-1][(*end)[1]]==0){
                new_ends.push_back({(*end)[0]-1, (*end)[1]});
                map[(*end)[0]-1][(*end)[1]]=n;
            }
            if (map[(*end)[0]][(*end)[1]-1]==0){
                new_ends.push_back({(*end)[0], (*end)[1]-1});
                map[(*end)[0]][(*end)[1]-1]=n;
            }
            if (map[(*end)[0]+1][(*end)[1]]==0){
                new_ends.push_back({(*end)[0]+1, (*end)[1]});
                map[(*end)[0]+1][(*end)[1]]=n;
            }
            if (map[(*end)[0]][(*end)[1]+1]==0){
                new_ends.push_back({(*end)[0], (*end)[1]+1});
                map[(*end)[0]][(*end)[1]+1]=n;
            }
            ++end;
        }
    }
}

void reset_map(std::vector<std::vector<int>>& map){
    for (std::vector<int>& v : map){
        for (int& i : v){
            if (i>0){i=0;}
        }
    }
}

void split_input(std::string line, int& x, int& y){
    std::string::iterator c = line.begin();
    std::string num_str;
    while(*c != ','){num_str.push_back(*c++);}
    x = stoi(num_str);
    num_str = "";
    while(++c != line.end()){num_str.push_back(*c);}
    y = stoi(num_str);
}

int main(){
    std::ifstream inputFile(filename);
    if(!inputFile.is_open()){
        std::cerr << "Error opening file: " << filename << "\n";
        return 1;
    }
    initialize_map(map);

    int x, y;
    for (int i = 0; i < input_num; ++i){
        getline(inputFile, line);
        split_input(line, x, y);
        map[y+1][x+1]=-1;
    }
    //print_map(map);
    std::cout << find_path(map) << "\n";
    while (getline(inputFile, line)){
        reset_map(map);
        //print_map(map);
        split_input(line, x, y);
        map[y+1][x+1]=-1;
        if(find_path(map)==0){std::cout << x << "," << y << "\n"; break;}
    }
    return 0;
}