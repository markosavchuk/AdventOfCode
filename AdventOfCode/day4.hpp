#ifndef day4_hpp
#define day4_hpp

#include <string>
#include <vector>

namespace Day4
{

std::vector<std::vector<int>> parseFile(const std::string& filepath);
std::vector<std::vector<int>> countAdjacent(const std::vector<std::vector<int>>& input);
    
int part1(const std::string& filepath);
int part2(const std::string& filepath);

}

#endif 
