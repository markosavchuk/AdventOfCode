#include "day8.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <array>
#include <unordered_set>

namespace Day8
{

using namespace std;

std::ostream& operator<<(std::ostream& os, const connection& con)
{
    os<<con.pos1.x<<","<<con.pos1.y<<","<<con.pos1.z<<" "<<con.pos2.x<<","<<con.pos2.y<<","<<con.pos2.z<<" "<<con.distance;
    return os;
}

std::ostream& operator<<(std::ostream& os, const vec3d& pos)
{
    os<<pos.x<<","<<pos.y<<","<<pos.z;
    return os;
}

struct vec3Hash
{
    std::size_t operator()(const vec3d& v) const
    {
        std::size_t h1 = std::hash<int>{}(v.x);
        std::size_t h2 = std::hash<int>{}(v.y);
        std::size_t h3 = std::hash<int>{}(v.z);

        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

vector<vec3d> readFile(string path)
{
    vector<vec3d> result;
    
    fstream file(path);
    string line;
    while (getline(file, line))
    {
        vec3d point;
        
        stringstream ss(line);
        int i = 0;
        string numStr;
        while (std::getline(ss, numStr, ','))
        {
            point[i++] = stoi(numStr);
        }
        
        result.push_back(point);
    }
    
    return result;
}

long distanceSquare(vec3d vec1, vec3d vec2)
{
    long dx = vec1.x - vec2.x;
    long dy = vec1.y - vec2.y;
    long dz = vec1.z - vec2.z;

    return dx*dx + dy*dy + dz*dz;
}

int part1(std::string path)
{
    constexpr int n = 1000;
    
    auto points = readFile(path);
    priority_queue<connection, vector<connection>> best;
    
    for (int i=0; i<points.size(); i++)
    {
        for (int j=i+1; j<points.size(); j++)
        {
            long dist = distanceSquare(points[i], points[j]);
            connection newCon{points[i], points[j], dist};
            if (best.size()<n)
            {
                best.push(newCon);
            }
            else
            {
                if (newCon < best.top())
                {
                    best.pop();
                    best.push(newCon);
                }
            }
        }
    }
        
    /// ---
    /// graph solution
    /// ---
    /*vector<connection> finalCons;
    while (!best.empty())
    {
        auto top = best.top();
        finalCons.push_back(top);
        best.pop();
    }
    
    unordered_map<vec3d, vector<vec3d>, vec3Hash> map;
    for (connection& con : finalCons)
    {
        map[con.pos1].push_back(con.pos2);
        map[con.pos2].push_back(con.pos1);
    }
    
    vector<unordered_set<vec3d, vec3Hash>> subgraphs;
    while (!map.empty())
    {
        auto startNode = map.begin()->first;
        unordered_set<vec3d, vec3Hash> subgraph {startNode};
        queue<vec3d> queue(std::deque<vec3d>(map[startNode].begin(), map[startNode].end()));
        
        while(!queue.empty())
        {
            vec3d current = queue.front();
            queue.pop();
            if (!subgraph.contains(current))
            {
                subgraph.insert(current);
                
                for (auto node : map[current])
                {
                    queue.push(node);
                }
            }
        }
        
        subgraphs.push_back(subgraph);
        
        for (auto node : subgraph)
        {
            map.erase(node);
        }
    }
    
    sort(subgraphs.begin(), subgraphs.end(),
        [](auto& a, auto& b){
            return a.size() > b.size();
        });
    
    int maxN = 3;
    int count = 1;
    for (int i=0; i<maxN; i++)
    {
        count*=subgraphs[i].size();
    }
    
    return count;*/
    
    
    /// ---
    /// DSU solution
    /// ---
    DSU<vec3d, vec3Hash> dsu;
    while (!best.empty())
    {
        auto& con = best.top();
        
        dsu.add(con.pos1);
        dsu.add(con.pos2);
        dsu.unite(con.pos1, con.pos2);
                
        best.pop();
    }
    
    unordered_map<vec3d, vector<vec3d>, vec3Hash> subgraphs;
    for (auto& [node, _] : dsu.parent)
    {
        vec3d root = dsu.find(node);
        subgraphs[root].push_back(node);
    }
    
    vector<int> sizes;
    for (auto& graph : subgraphs)
    {
        sizes.push_back((int)graph.second.size());
    }
    
    sort(sizes.begin(), sizes.end(), greater<int>());
    
    constexpr int maxN = 3;
    
    int count = 1;
    for (int i=0; i<maxN; i++)
    {
        count*=sizes[i];
    }
    
    return count;
}

long part2(std::string path)
{
    auto points = readFile(path);
    
    vector<connection> vertices;
    
    for (int i=0; i<points.size(); i++)
    {
        for (int j=i+1; j<points.size(); j++)
        {
            long dist = distanceSquare(points[i], points[j]);
            connection newCon{points[i], points[j], dist};
            vertices.push_back(newCon);
        }
    }
    
    sort(vertices.begin(), vertices.end());
    
    connection last {};
    
    int i=0;
    DSU<vec3d, vec3Hash> dsu;
    while (true)
    {
        last = vertices[i++];

        dsu.add(last.pos1);
        dsu.add(last.pos2);
        dsu.unite(last.pos1, last.pos2);

        unordered_map<vec3d, vector<vec3d>, vec3Hash> subgraphs;
        for (auto& [node, _] : dsu.parent)
        {
            vec3d root = dsu.find(node);
            subgraphs[root].push_back(node);
        }
        
        if (subgraphs.size()==1 && subgraphs.begin()->second.size()==points.size())
        {
            break;
        }
    }
    
    return (long)last.pos1.x * last.pos2.x;
}

}
