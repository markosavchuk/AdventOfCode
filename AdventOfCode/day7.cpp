#include "day7.hpp"
#include <fstream>
#include <iostream>
#include <string>

namespace Day7
{

using namespace std;

vector<vector<long>> readFile(std::string path)
{
    vector<vector<long>> result;
    
    fstream file(path);
    string line;
    while (getline(file, line))
    {
        auto vec = vector<long>(line.length(), 0);
        for (int j=0; j<line.length(); j++)
        {
            switch (line[j]) {
                case 'S':
                    vec[j] = 1;
                    break;
                case '^':
                    vec[j] = -1;
                    break;
            }
        }
        
        result.push_back(vec);
    }
    
    return result;
}

int part1(string path)
{
    int count = 0;
    
    auto input = readFile(path);
    
    for (int i=1; i<input.size(); i++)
    {
        for (int j=0; j<input[i].size(); j++)
        {
            if (input[i-1][j] == 1)
            {
                if (input[i][j] == 0)
                {
                    input[i][j] = 1;
                }
                else if (input[i][j] == -1)
                {
                    bool splitted = false;
                                        
                    if (j>0 && input[i][j-1]==0)
                    {
                        input[i][j-1] = 1;
                        splitted = true;
                    }
                    
                    if (j<input.size()-1 && input[i][j+1]==0)
                    {
                        input[i][j+1] = 1;
                        splitted = true;
                    }
                    
                    if (splitted)
                    {
                        count++;
                    }
                }
            }
        }
    }
    
    return count;
}

long part2(string path)
{
    long count = 0;
    
    auto input = readFile(path);
    
    for (int i=1; i<input.size(); i++)
    {
        for (int j=0; j<input[i].size(); j++)
        {
            if (input[i-1][j] == 1)
            {
                if (input[i][j] == 0)
                {
                    input[i][j] = 1;
                }
                else if (input[i][j] == -1)
                {
                    if (j>0 && input[i][j-1]==0)
                    {
                        input[i][j-1] = 1;
                    }
                    
                    if (j<input.size()-1 && input[i][j+1]==0)
                    {
                        input[i][j+1] = 1;
                    }
                }
            }
        }
    }
    
    for (int i = (int)input.size()-2; i>=0; i--)
    {
        for (int j=1; j<input[i].size()-1; j++)
        {
            if (input[i][j]==-1)
            {
                input[i][j] = input[i+1][j-1] + input[i+1][j+1];
            }
            else
            {
                input[i][j] = input[i+1][j];
            }
            
            if (input[i][j]>count)
            {
                count = input[i][j];
            }
        }
    }
    
    return count;
}

}
