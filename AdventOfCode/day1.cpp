#include "day1.hpp"

#include <iostream>
#include <fstream>

namespace Day1
{

const static int clock = 100;
const static int start_value = 50;

int part1(std::string inputPath)
{
    std::ifstream file(inputPath);
 
    int count = 0;
    int value = start_value;
    
    std::string str;
    while (file>>str)
    {
        int moveValue = std::stoi(str.substr(1));
        if (str[0]=='L')
        {
            moveValue*= -1;
        }
        
        value = processStep(value, moveValue);
        if (value == 0)
        {
            count++;
        }
    }
    
    return count;
}

int part2(std::string inputPath)
{
    std::ifstream file(inputPath);
 
    int count = 0;
    int value = start_value;
    
    std::string str;
    while (file>>str)
    {
        int moveValue = std::stoi(str.substr(1));
        if (moveValue>clock)
        {
            int rounds = moveValue/clock;
            count += rounds;
            moveValue -= (moveValue/clock)*clock;
        }
        
        if (str[0]=='L')
        {
            moveValue*= -1;
        }
        
        int valueStep = processStep(value, moveValue);
        
        if ((valueStep!=0 && value!=0) && ((moveValue>0 && valueStep<value) || (moveValue<0 && valueStep>value)))
        {
            count++;
        }
        
        value = valueStep;
        if (value == 0)
        {
            count++;
        }
    }
    
    return count;
}

int processStep(int start, int move)
{
    return ((start + move) % clock + clock) % clock;
}

}
