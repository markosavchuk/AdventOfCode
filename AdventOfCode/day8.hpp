#ifndef day8_hpp
#define day8_hpp

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

namespace Day8
{

struct vec3d
{
    int x, y, z;
    
    int& operator[](int i)
    {
        return *(&x + i);
    }
    
    bool operator==(const vec3d& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

struct connection
{
    vec3d pos1;
    vec3d pos2;
    long distance;
    
    bool operator<(const connection& other) const
    {
        return distance < other.distance;
    }
};

template<typename T, typename Hash = std::hash<T>>
struct DSU {
    std::unordered_map<T, T, Hash> parent;
    std::unordered_map<T, int, Hash> size;

    void add(const T& x)
    {
        if (!parent.count(x)) {
            parent[x] = x;
            size[x] = 1;
        }
    }

    T find(const T& x)
    {
        auto it = parent.find(x);
        if (it->second == x) return x;
        return it->second = find(it->second);
    }

    void unite(const T& a, const T& b)
    {
        T rootA = find(a);
        T rootB = find(b);
        if (rootA == rootB) return;

        if (size[rootA] < size[rootB])
            std::swap(rootA, rootB);

        parent[rootB] = rootA;
        size[rootA] += size[rootB];
    }
};

long distanceSquare(vec3d vec1, vec3d vec2);
std::vector<vec3d> readFile(std::string path);
int part1(std::string path);
long part2(std::string path);

}
#endif /* day8_hpp */
