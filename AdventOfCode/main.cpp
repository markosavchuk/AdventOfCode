#include <iostream>
#include <fstream>

using namespace std;

string folder = "inputs";

void readFile(string name, vector<int>& outVector)
{
    string path = std::format("{}/{}", folder, name);
    ifstream file(path);
    
    int value;
    while (file>>value)
    {
        outVector.push_back(value);
    }
}

int main(int argc, const char * argv[])
{
    //todo setup git
    
    //vector<int> numbers;
    //readFile("day1.txt", numbers);
}
