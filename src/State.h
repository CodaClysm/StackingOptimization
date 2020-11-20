#pragma once
#include <vector>
#include <string>
using namespace std;
class State
{
public:
    vector<vector<vector<bool>>> state;
    State();
    string toString();
    string toString_h();

};

