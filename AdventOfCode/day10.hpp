#ifndef day10_hpp
#define day10_hpp

#include <string>
#include <vector>
#include <bitset>
#include <array>
#include <iostream>
#include <algorithm>

namespace Day10
{

class NBaseNumber
{
    std::array<int, 256> digits{};
    int base;
    std::size_t size;

public:
    NBaseNumber(int base, std::size_t size) : base(base), size(size)
    {
    }
    
    bool increment()
    {
        int carry = 1;
        for (std::size_t i = 0; i < size; ++i)
        {
            int sum = digits[i] + carry;
            digits[i] = sum % base;
            carry = sum / base;
        }
        
        return carry == 0;
    }

    void print() const
    {
        for (std::size_t i = size; i-- > 0;)
        {
            std::cout << digits[i];
        }
        std::cout << std::endl;
    }

    int operator[](std::size_t idx) const { return digits[idx]; }
    int& operator[](std::size_t idx) { return digits[idx]; }
};

//typedef uint16_t code;
typedef std::bitset<10> code;

code parseTarget(std::stringstream& ss);
code parseSwitch(std::stringstream& ss);
std::vector<int> parseJoltages(std::stringstream& ss);
void readFile(std::string& path, std::vector<code>& targets, std::vector<std::vector<code>>& switches, std::vector<std::vector<int>>& joltages);

int countSwitches(code target, std::vector<code>& switches);
int part1(std::string path);
long part2(std::string path);

}

#endif /* day10_hpp */
