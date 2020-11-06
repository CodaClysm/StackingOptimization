#pragma once
#include "State.h"
#include "Shape.h"
#include <vector>
using namespace std;
class Environment
{
private:
    State currentState;
public:
    Environment();
    vector<State> getPossibleStates(Shape shape);
    void updateState(State s);
    State getCurrentState();
};

