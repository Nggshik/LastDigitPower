#include <list>
#include <iostream>
#include <array>

using namespace std;

constexpr std::array<std::array<int,4>,10> posabilities{ {{0,0,0,0},{1,1,1,1},{2,4,8,6},{3,9,7,1},{4,6,4,6},{5,5,5,5},{6,6,6,6},{7,9,3,1},{8,4,2,6},{9,1,9,1} }};

int last_digit_helper(int value, int power)
{
    if(power == 0)
        return 1;
    if(power == 1)
        return value;

    return posabilities[value%10][(power-1)%4]; 
}


int last_digit(list<int> array) {
    // Write your code here
    auto res = array.back();
    array.pop_back();
    
    while(!array.empty())
    {
        auto last = array.back();
        array.pop_back();
        res = last_digit_helper(last,res);
    }
}


int main()
{
     std::cout << last_digit({3,4,5}) << std::endl;
}