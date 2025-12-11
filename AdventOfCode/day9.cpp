#include "day9.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <unordered_map>

namespace Day9
{

using namespace std;

struct pointHash
{
    std::size_t operator()(const point& p) const
    {
        uint64_t key = (uint64_t(uint32_t(p.x)) << 32) ^ uint32_t(p.y);
        return std::hash<uint64_t>{}(key);
    }
};

vector<point> readFile(string path)
{
    vector<point> res;
    
    fstream file(path);
    string line;
    while (getline(file, line))
    {
        std::stringstream ss(line);

        int a, b;
        char comma;
        ss >> a >> comma >> b;
        
        res.push_back({a, b});
    }
    
    return res;
}

long cross(const point& a, const point& b, const point& c)
{
    return 1L * (b.x - a.x) * (c.y - a.y) -
           1L * (b.y - a.y) * (c.x - a.x);
}

bool onSegment(const point& a, const point& b, const point& p)
{
    if (cross(a, b, p) != 0)
    {
        return false;
    }
    
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

unordered_map<point, bool, pointHash> pointsCache{};
bool pointInPolygon(const vector<point>& poly, const point& p)
{
    if (pointsCache.contains(p))
    {
        return pointsCache[p];
    }
    
    bool inside = false;
    int n = (int)poly.size();

    for (int i = 0, j = n - 1; i < n; j = i++) {
        const point& a = poly[j];
        const point& b = poly[i];

        if (onSegment(a, b, p))
        {
            pointsCache[p] = true;
            return true;
        }

        bool intersect =
            ((a.y > p.y) != (b.y > p.y)) &&
            (p.x < (long double)(b.x - a.x) * (p.y - a.y) / (b.y - a.y) + a.x);

        if (intersect)
        {
            inside = !inside;
        }
    }

    pointsCache[p] = inside;
    return inside;
}

bool polygonInsidePolygon(const vector<point>& A, const vector<point>& B)
{
    int nA = (int)A.size();
    int nB = (int)B.size();

    for (auto& p : A)
    {
        if (!pointInPolygon(B, p))
        {
            return false;
        }
    }

    for (int i = 0; i < nA; i++)
    {
        point A1 = A[i];
        point A2 = A[(i + 1) % nA];

        for (int j = 0; j < nB; j++)
        {
            point B1 = B[j];
            point B2 = B[(j + 1) % nB];

            long c1 = cross(A1, A2, B1);
            long c2 = cross(A1, A2, B2);
            long c3 = cross(B1, B2, A1);
            long c4 = cross(B1, B2, A2);

            bool proper =
                ((c1 > 0 && c2 < 0) || (c1 < 0 && c2 > 0)) &&
                ((c3 > 0 && c4 < 0) || (c3 < 0 && c4 > 0));

            if (proper)
            {
                return false;
            }
        }
    }

    return true;
}

long calculateSquare(point a, point b)
{
    return (long)(abs(a.x - b.x)+1) * ((a.y - b.y)+1);
}

long part1(string path)
{
    long count = 0;
    
    auto input = readFile(path);
    
    for (int i=0; i<input.size(); i++)
    {
        for (int j=i+1; j<input.size(); j++)
        {
            long current = calculateSquare(input[i], input[j]);
            
            if (current > count)
            {            
                count = current;
            }
        }
    }
    
    return count;
}

long part2(string path)
{
    long count = 0;
    
    auto input = readFile(path);
    
    //--- Measurement
    auto start = std::chrono::high_resolution_clock::now();
    //---
    
    for (int i=0; i<input.size(); i++)
    {
        for (int j=i+1; j<input.size(); j++)
        {
            point a = input[i];
            point b = input[j];
            long current = calculateSquare(a, b);
            
            if (current <= count)
            {
                continue;
            }
            
            vector<point> square{{a.x, a.y}, {b.x, a.y}, {b.x, b.y}, {a.x, b.y}};
            
            if (polygonInsidePolygon(square, input))
            {
                count = current;
            }            
        }
    }
    
    //--- Measurement
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "time: " << duration.count()*1000 << " ms" << std::endl;
    //---
    
    return count;
}

}
