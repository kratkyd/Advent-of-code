//needed a big hint for this one
//also, shit solution. There must be some good recursive way to do it, but I've spent uncomfortable time on this

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

std::vector<std::vector<long long>> testinput = {{125, 1}, {17, 1}};
std::vector<std::vector<long long>> input = {{7725, 1}, {185, 1}, {2, 1}, {132869, 1}, {0, 1}, {1840437, 1}, {62, 1}, {26310, 1}};

void blink(std::vector<std::vector<long long>>& nums){
    std::vector<std::vector<long long>> vals;
    for (int i = 0; i < nums.size(); ++i){
        int exp = floor(log10(nums[i][0]));
        if (nums[i][0] == 0){
            vals.push_back({1, nums[i][1]});
        } else if (exp%2==1){
            vals.push_back({nums[i][0]/(long long)pow(10, (exp+1)/2), nums[i][1]});
            vals.push_back({nums[i][0]%(long long)pow(10, (exp+1)/2), nums[i][1]}); 
        } else {
            vals.push_back({nums[i][0]*2024, nums[i][1]});
        }
        nums[i][1] = 0;
    }
    for (std::vector<long long> v : vals){
        bool already_in = false;
        for (std::vector<long long>& num : nums){
            if (num[0] == v[0]){
                num[1] += v[1];
                already_in = true;
            }
        }
        if (!already_in){
            nums.push_back({v[0], v[1]});
        }
    } 
}

int main(){
    for (int i = 0; i < 25; ++i){
        blink(input);
    }
    long long sum = 0;
    for (std::vector<long long> v : input){
        sum += v[1];
    }
    std::cout << "First answer: " << sum << std::endl;
    for (int i = 25; i < 75; ++i){
        blink(input);
    }
    sum = 0;
    for (std::vector<long long> v : input){
        sum += v[1];
    }
    std::cout << "Second answer: " << sum << std::endl;
    return 0;
}