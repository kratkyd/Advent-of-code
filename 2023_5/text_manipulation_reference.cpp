#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// just so I have reference as to how to work with text

void print_file(std::string file_name){
    std::string line;
    std::ifstream myfile (file_name);
    if (myfile.is_open())
    {
    while ( getline (myfile,line) )
    {
        std::cout << line << '\n';
    }
    myfile.close();
    }

    else std::cout << "Unable to open file"; 
}

void separate_by(std::string text, char separator){
    std::istringstream input;
    input.str(text);
    for (std::string line; std::getline(input, line, separator);)
        std::cout << line << '\n';
}

int main () {
    separate_by("h,h+,jd,+,k",',');
    return 0;
}