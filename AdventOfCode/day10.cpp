#include "day10.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>

namespace Day10
{

using namespace std;

code parseSwitch(stringstream& ss)
{
    code mask = 0;
    int n;
    char c;

    while (ss >> n)
    {
        mask |= (1u << n);
        
        ss >> c;
        if (c == ')')
        {
            break;
        }
    }
    
    return mask;
}

code parseTarget(stringstream& ss)
{
    code mask = 0;
    int bit = 0;
    char c;

    while (ss >> c && c != ']')
    {
        if (c == '#')
        {
            mask |= (1u << bit);
        }
        
        bit++;
    }
    return mask;
}

vector<int> parseJoltages(stringstream& ss)
{
    vector<int> res;
    
    int n;
    char c;

    while (ss >> n)
    {
        res.push_back(n);
        
        ss >> c;
        if (c == '}')
        {
            break;
        }
    }
    
    return res;
}

void readFile(string& path, vector<code>& targets, vector<vector<code>>& switches, vector<vector<int>>& joltages)
{
    fstream file(path);
    
    string line;
    while (getline(file, line))
    {
        code target = 0;
        vector<code> currentSwitches;
        
        stringstream ss(line);
        char c;
        while (ss >> c)
        {
            if (c == '[')
            {
                target = parseTarget(ss);
            }
            else if (c == '(')
            {
                currentSwitches.push_back(parseSwitch(ss));
            }
            else if (c == '{')
            {
                joltages.push_back(parseJoltages(ss));
            }
        }
        
        targets.push_back(target);
        switches.push_back(currentSwitches);
    }
}

int countSwitches(code target, vector<code>& switches)
{
    int size = (int)switches.size();
    int k = 1;
    code current = target;
    
    NBaseNumber permutation(size, k);
    
    while (true)
    {
        current = target;
        for (int i=0; i<k; i++)
        {
            current ^= switches[permutation[i]];
        }
        
        if (current==0)
        {
            return k;
        }
        
        if (!permutation.increment())
        {
            permutation = NBaseNumber(size, ++k);
        }
    }
    
    return k;
}

int part1(std::string path)
{
    int count = 0;
    
    vector<code> targets;
    vector<vector<code>> switches;
    vector<vector<int>> joltages;
    readFile(path, targets, switches, joltages);
    
    for (int i=0; i<targets.size(); i++)
    {        
        count += countSwitches(targets[i], switches[i]);;
    }
    
    return count;
}

}
