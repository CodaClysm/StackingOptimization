#include "Environment.h"

Environment::Environment()
{

}

vector<State> Environment::getPossibleStates(Shape shape)
{

}

void Environment::updateState(State s)
{
    currentState = s;
}

State Environment::getCurrentState()
{
    return currentState;
}