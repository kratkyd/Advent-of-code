#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

std::string filename = "input";
std::string line;
int room_height = 103;
int room_width = 101;
std::vector<std::vector<int>> map;

void final_position(int& x, int& y, int vx, int vy){
    x = ((x+100*vx)%room_width+room_width)%room_width;
    y = ((y+100*vy)%room_height+room_height)%room_height;
}

int main(){
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()){
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }
    std::regex num_regex(R"(-?\d+)");
    int x, y, vx, vy, quad0=0, quad1=0, quad2=0, quad3=0;
    while(getline(inputFile, line)){
        auto nums = std::sregex_iterator(line.begin(), line.end(), num_regex);
        x = stoi((*nums++).str());
        y = stoi((*nums++).str());
        vx = stoi((*nums++).str());
        vy = stoi((*nums).str());
        final_position(x, y, vx, vy);
        if (x<room_width/2 && y<room_height/2){++quad0;}
        else if (x<room_width/2 && y>room_height/2){++quad1;}
        else if (x>room_width/2 && y<room_height/2){++quad2;}
        else if (x>room_width/2 && y>room_height/2){++quad3;}
    }
    std::cout << quad0 << " " << quad1 << " " << quad2 << " " << quad3 << std::endl;
    std::cout << quad0*quad1*quad2*quad3 <<std::endl;
    return 0;
}