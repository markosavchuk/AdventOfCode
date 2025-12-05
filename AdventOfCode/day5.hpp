#ifndef day5_hpp
#define day5_hpp

#include <vector>
#include <string>
#include <utility>

namespace Day5
{

void readFile(std::string path, std::vector<std::pair<long, long>>& outRanges, std::vector<long>& outIds, bool ignoreIds = false);
int part1(std::string inputPath);
long part2(std::string inputPath);

}

#endif /* day5_hpp */
