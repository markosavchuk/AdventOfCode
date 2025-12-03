#include "day3.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

namespace Day3
{

using namespace std;

int findMaxIndex(const std::string& str, int begin, int end)
{
    char bestChar = str[begin];
    int bestIndex = begin;
    
    for (int i=begin; i<end; i++)
    {
        char c = str[i];
        if (c > bestChar)
        {
            bestChar = c;
            bestIndex = i;
        }
    }
    
    return bestIndex;
}

long process(std::string inputPath, int digits)
{
    ifstream file(inputPath);
    
    const int elements = digits;
    
    long count = 0;
    
    string line;
    while (getline(file, line))
    {
        string resStr = "";
        int beginIndex = 0;
        int length = (int)line.length();
        for (int i=elements-1; i>=0; i--)
        {
            int maxIndex = findMaxIndex(line, beginIndex, length-i);
            resStr += line[maxIndex];
            beginIndex = maxIndex+1;
        }
        
        long res = stol(resStr);
        count += res;
    }
    
    return count;
}

long part1(std::string inputPath)
{
    return process(inputPath, 2);
}

long part2(std::string inputPath)
{
    return process(inputPath, 12);
}

}
