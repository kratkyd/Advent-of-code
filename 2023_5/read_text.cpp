#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

const std::string file_name = "test_file.txt";

void make_seeds_arr(int arr[]){
    std::string line;
    std::ifstream myfile (file_name);
    while(std::getline(myfile, line)){
	std::cout << line << '\n';
    }
    //if (myfile.is_open()){
    //    getline(myfile, line);
    //    std::cout << line << '\n';
    //    myfile.close();
    //} else std::cout << "Unable to open file";
}

int main(){
    int arr[5] = {1,2,3,4,5};
    make_seeds_arr(arr);
}
