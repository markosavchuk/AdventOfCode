#include "day4.hpp"

#include <fstream>
#include <vector>
#include <algorithm>

namespace Day4
{

using namespace std;

vector<vector<int>> parseFile(const std::string& filepath)
{
    std::vector<std::vector<int>> result;
    
    ifstream file(filepath);
    string line;
    while (getline(file, line))
    {
        std::vector<int> resultLine;
        resultLine.push_back(0);
        for (char c : line)
        {
            resultLine.push_back(c == '@');
        }
        resultLine.push_back(0);
        result.push_back(resultLine);
    }
    
    // Adding zero around matrix
    result.insert(result.begin(), vector<int>(result[0].size(), 0));
    result.emplace_back(result[0].size(), 0);
    
    return result;
}

vector<vector<int>> countAdjacent(const vector<vector<int>>& input)
{
    vector<vector<int>> result = input;
    for (int i=1; i<input.size()-1; i++)
    {
        for (int j=1; j<input[i].size()-1; j++)
        {
            result[i][j] =
                input[i-1][j-1] + input[i-1][j] + input[i-1][j+1] +
                input[i][j-1] + input[i][j+1] +
                input[i+1][j-1] + input[i+1][j] + input[i+1][j+1];
            
        }
    }
    
    return result;
}

int part1(const std::string& filepath)
{
    auto parsedVec = Day4::parseFile(filepath);
    auto countVec = Day4::countAdjacent(parsedVec);
    
    int count = 0;
    for (int i=1; i<countVec.size()-1; i++)
    {
        for (int j=1; j<countVec[i].size()-1; j++)
        {
            if (parsedVec[i][j] == 1 && countVec[i][j] <= 3)
            {
                count++;
            }
        }
    }
    
    return count;
}

int part2(const std::string& filepath)
{
    auto parsedVec = Day4::parseFile(filepath);
    auto countVec = Day4::countAdjacent(parsedVec);

    int count = 0;

    while (true)
    {
        bool ready = true;
        for (int i=1; i<countVec.size()-1; i++)
        {
            for (int j=1; j<countVec[i].size()-1; j++)
            {
                if (parsedVec[i][j] == 1 && countVec[i][j] <= 3)
                {
                    ready = false;
                
                    parsedVec[i][j] = 0;
                
                    countVec[i-1][j-1] = std::clamp(countVec[i-1][j-1]-1,0,9);
                    countVec[i-1][j] = std::clamp(countVec[i-1][j]-1,0,9);
                    countVec[i-1][j+1] = std::clamp(countVec[i-1][j+1]-1,0,9);
                    countVec[i][j-1] = std::clamp(countVec[i][j-1]-1,0,9);
                    countVec[i][j+1] = std::clamp(countVec[i][j+1]-1,0,9);
                    countVec[i+1][j-1] = std::clamp(countVec[i+1][j-1]-1,0,9);
                    countVec[i+1][j] = std::clamp(countVec[i+1][j]-1,0,9);
                    countVec[i+1][j+1] = std::clamp(countVec[i+1][j+1]-1,0,9);
                
                    count++;
                }
            }
        }
    
        if (ready)
        {
            break;
        }
    }
    
    return count;
}

}
