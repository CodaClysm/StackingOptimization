#pragma once
#include <vector>

using namespace std;
class State
{
public:
    vector<vector<vector<bool>>> state;
    State() = default;
    State(int x, int y, int z);
    void print();

};

