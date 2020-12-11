#pragma once
#include "State.h"
#include "Shape.h"
#include <vector>
using namespace std;
class Environment
{
private:
    State currentState;
    State testShape(int x, int z, int y, Shape shape);
    bool isCollision(State shapeState);
    State mergeStates(State ShapeState);

public:
    Environment();
    vector<State> getPossibleStates(Shape shape);
    void updateState(State s);
    State getCurrentState();
};

