#include "day6.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

namespace Day6
{

using namespace std;

long calculate(std::vector<std::tuple<std::vector<int>, int>>& input)
{
    long count = 0;
    
    for (auto tuple : input)
    {
        bool multiply = get<1>(tuple);
        long rowCount = multiply ? 1 : 0;
        
        for (auto number : get<0>(tuple))
        {
            if (multiply)
            {
                rowCount*= number;
            }
            else
            {
                rowCount+= number;
            }
        }
        
        count += rowCount;
    }
    
    return count;
}

vector<tuple<vector<int>, int>> readFilePart1(std::string filePath)
{
    vector<tuple<vector<int>, int>> input{};
    
    fstream file(filePath);
    
    bool fisrtLine = true;
    string line;
    
    while (getline(file, line))
    {
        istringstream iss(line);
        int number;
        int i = 0;
        while (iss >> number)
        {
            if (fisrtLine)
            {
                input.push_back(tuple<vector<int>, int>{});
            }
            
            get<0>(input[i]).push_back(number);
            
            i++;
        }
        
        if (i==0)
        {
            iss.clear();
            iss.seekg(0);
            char symbol;
            while (iss >> symbol)
            {
                get<1>(input[i]) = symbol=='*';
                
                i++;
            }
        }
        
        fisrtLine = false;
    }
    
    return input;
}

vector<tuple<vector<int>, int>> readFilePart2(std::string filePath)
{
    vector<tuple<vector<int>, int>> input{};
    
    fstream file(filePath);
    
    vector<string> inputStr;
    
    string line;
    while (getline(file, line))
    {
        inputStr.push_back(line);
    }
    
    int columnIndex = 0;
    input.push_back(tuple<vector<int>, int>{});
    
    for (int i=0; i<inputStr[0].length(); i++)
    {
        string numberStr = "";
        for (int j=0; j<inputStr.size(); j++)
        {
            char digit = inputStr[j][i];
            
            if (isdigit(digit))
            {
                numberStr+= digit;
            }
            else if (digit == ' ')
            {
                continue;
            }
            else
            {
                get<1>(input[columnIndex]) = digit == '*';
            }
        }
        
        if (numberStr.empty())
        {
            input.push_back(tuple<vector<int>, int>{});
            columnIndex++;
        }
        else
        {
            int number = stoi(numberStr);
            get<0>(input[columnIndex]).push_back(number);
        }
        
    }
    
    return input;
}

long part1(std::string filePath)
{
    auto input = readFilePart1(filePath);
    return calculate(input);
}

long part2(std::string filePath)
{
    auto input = readFilePart2(filePath);
    return calculate(input);
}

}
