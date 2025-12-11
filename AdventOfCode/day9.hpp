#ifndef day9_hpp
#define day9_hpp

#include <vector>
#include <string>
#include <iostream>
#include <cstddef>

namespace Day9
{

struct point
{
    int x;
    int y;
    
    bool operator==(const point& other) const
    {
        return x == other.x && y == other.y;
    }
};

std::vector<point> readFile(std::string path);

long cross(const point& a, const point& b, const point& c);
bool onSegment(const point& a, const point& b, const point& p);
bool pointInPolygon(const std::vector<point>& poly, const point& p);
bool polygonInsidePolygon(const std::vector<point>& A, const std::vector<point>& B);
long calculateSquare(point a, point b);

long part1(std::string path);
long part2(std::string path);


}

#endif /* day9_hpp */
