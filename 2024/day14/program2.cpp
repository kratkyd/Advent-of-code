//Okay, so this solution is also kind of stupid and should be remade. I figured, since in the first level I had to 
//separate robots into quadrants, that the image would be in one of the quardants, so the function just checks, when
//most (more than 1/3, not most then, doesn't work for 1/2 because the image isn't in one of the quadrants) robots are
//in one of the quadrants. 1/3 works and 1/2 doesn't since the image isn't actually in one of the quadrants.


// !!important!! The program won't give you a solution, it will instead loop infinitely. I solved the problem using
//vscode's debug option, skiping through "test_entropy"'s finds until I found the image. For this one I required
//help in form of a hint what the "christmas tree" might look like, but the solution is mine.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

std::string filename = "input";
std::string line;
int room_height = 103;
int room_width = 101;
int robots_num = 0, steps = 0;
std::vector<std::vector<int>> robots;

void print_map(std::vector<std::vector<int>> robots){
    std::cout << "\n\n\n\n\n\n\n\n";
    std::vector<std::vector<char>> map;
    for (int i = 0; i < room_height; ++i){
        std::vector<char> vec;
        for (int j = 0; j < room_width; ++j){
            vec.push_back(' ');
        }
        map.push_back(vec);
    }

    for (std::vector<int> v : robots){
        map[v[1]][v[0]] = '.';
    }

    for (std::vector<char> v : map){
        for(char c : v){
            std::cout << c << " ";
        }
        std::cout << "\n";
    }
}

void test_entropy(std::vector<std::vector<int>> robots){
    int quad0=0, quad1=0, quad2=0, quad3=0;
    for (std::vector<int> v : robots){
        if (v[0]<room_width/2 && v[1]<room_height/2){++quad0;}
        else if (v[0]<room_width/2 && v[1]>room_height/2){++quad1;}
        else if (v[0]>room_width/2 && v[1]<room_height/2){++quad2;}
        else if (v[0]>room_width/2 && v[1]>room_height/2){++quad3;}
    }
    std::cout << quad0 << " " << quad1 << " " << quad2 << " " << quad3 << " " << robots_num << std::endl;
    if (quad0>robots_num/3 || quad1>robots_num/3 || quad2>robots_num/3 || quad3>robots_num/3){
        print_map(robots);
        std::cout << time << std::endl;
    }
}

void step(std::vector<std::vector<int>>& vals, int& time){
    for (std::vector<int>& v : vals){
        v[0] = ((v[0]+v[2])%room_width+room_width)%room_width;
        v[1] = ((v[1]+v[3])%room_height+room_height)%room_height;
    }
    ++steps;
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
        std::vector<int> robot = {x, y, vx, vy};
        robots.push_back(robot);
        ++robots_num;
    }
    while(true){
        step(robots, steps);
        test_entropy(robots);
    }
    return 0;
}