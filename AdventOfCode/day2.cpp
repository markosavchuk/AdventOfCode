#include "day2.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

namespace Day2
{

using namespace std;

vector<string> readFile(string inputPath)
{
    ifstream file(inputPath);
    
    vector<string> ranges;
    string line;
    string range;

    getline(file, line);
    stringstream ss(line);

    while (getline(ss, range, ','))
    {
        ranges.push_back(range);
    }
    
    return ranges;
}

long part1(string inputPath)
{
    long count = 0;
    
    auto ranges = readFile(inputPath);
    
    for (auto range : ranges)
    {
        auto separator = range.find('-');
        
        auto beginStr = range.substr(0, separator);
        auto endStr = range.substr(separator+1, range.length());
        
        int endLength = (int)endStr.length();
        
        string part1Str = "";
        string part2Str = "";
        
        while (true)
        {
            int beginLength = (int)beginStr.length();
            
            if (beginLength%2 != 0)
            {
                beginStr = "1";
                for (int i=0; i<beginLength; i++)
                {
                    beginStr += "0";
                }
                
                beginLength++;
            }
                                        
            if ((beginLength == endLength && beginStr > endStr) || (beginLength > endLength))
            {
                break;
            }
            
            int halfSize = beginLength/2;
            string part1Str = beginStr.substr(0, halfSize);
            string part2Str = beginStr.substr(halfSize, halfSize);
            
            if (part1Str==part2Str)
            {
                count += stol(beginStr);
            }
            
            long begin = stol(beginStr);
            begin++;
            beginStr = to_string(begin);
        }

    }
    
    return count;
}

long part2(string inputPath)
{
    long count = 0;
    
    auto ranges = readFile(inputPath);
    
    for (auto range : ranges)
    {
        auto separator = range.find('-');
        
        auto beginStr = range.substr(0, separator);
        auto endStr = range.substr(separator+1, range.length());
        
        int endLength = (int)endStr.length();
        
        string part1Str = "";
        string part2Str = "";
        
        while (true)
        {
            int beginLength = (int)beginStr.length();
            
            if ((beginLength == endLength && beginStr > endStr) || (beginLength > endLength))
            {
                break;
            }
            
            for (int devider = 2; devider<=beginLength; devider++)
            {
                if (beginLength % devider != 0)
                {
                    continue;
                }
                
                int partLength = beginLength/devider;
                string partStr = beginStr.substr(0, partLength);
                string otherPart;
                
                for (int i=1; i<devider; i++)
                {
                    otherPart = beginStr.substr(i*partLength, partLength);
                    if (partStr != otherPart)
                    {
                        break;
                    }
                }
                
                if (partStr == otherPart)
                {
                    count += stol(beginStr);
                    break;
                }
            }
            
            long begin = stol(beginStr);
            begin++;
            beginStr = to_string(begin);
        }

    }
    
    return count;
}

}
