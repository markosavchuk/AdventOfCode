#ifndef day6_hpp
#define day6_hpp

#include <string>
#include <vector>
#include <tuple>

namespace Day6
{
long calculate(std::vector<std::tuple<std::vector<int>, int>>& input);

std::vector<std::tuple<std::vector<int>, int>> readFilePart1(std::string filePath);
long part1(std::string filePath);

std::vector<std::tuple<std::vector<int>, int>> readFilePart2(std::string filePath);
long part2(std::string filePath);

}

#endif /* day6_hpp */
