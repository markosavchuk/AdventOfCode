#include "day5.hpp"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <set>

namespace Day5
{

using namespace std;

void readFile(string path, vector<std::pair<long, long>>& outRanges, vector<long>& outIds, bool ignoreIds)
{
    ifstream file(path);
    
    bool readRanges = true;
    
    string line;
    while (getline(file, line))
    {
        if (line.length()==0)
        {
            readRanges = false;
            if (ignoreIds)
            {
                break;
            }
            else
            {
                continue;
            }
        }
        
        if (readRanges)
        {
            auto pos = line.find('-');
            long a = std::stol(line.substr(0, pos));
            long b = std::stol(line.substr(pos + 1));
            outRanges.push_back({a,b});
        }
        else
        {
            outIds.push_back(std::stol(line));
        }
    }
}

int part1(string inputPath)
{
    int count = 0;
    
    vector<std::pair<long, long>> ranges;
    vector<long> ids;
    readFile(inputPath, ranges, ids);
    
    for (auto id : ids)
    {
        for (auto range : ranges)
        {
            if (id>=range.first && id<=range.second)
            {
                count++;
                break;
            }
        }
    }
    
    return count;
}

long part2(string path)
{
    long count = 0;
    
    vector<std::pair<long, long>> ranges;
    vector<long> ids;
    readFile(path, ranges, ids, true);
    
    for (int i=0; i<ranges.size(); i++)
    {
        for (int j=0; j<ranges.size(); j++)
        {
            auto range1 = ranges[i];
            auto range2 = ranges[j];
                        
            if (range1==range2)
            {
                continue;
            }
            
            if (range1.first <= range2.second && range2.first <= range1.second)
            {
                range1.first = min(range1.first, range2.first);
                range1.second = max(range1.second, range2.second);
                
                ranges[i] = range1;
                ranges[j] = range1;
            }
        }
    }
    
    set<std::pair<long, long>> uniqueRanges(ranges.begin(), ranges.end());
    
    for (auto range : uniqueRanges)
    {
        count+= range.second-range.first+1;
    }
    
    return count;
}

}
