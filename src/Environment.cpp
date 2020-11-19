#include "Environment.h"

Environment::Environment(Shape envShape)
{
    currentState = State(envShape.getX(), envShape.getY(), envShape.getZ());
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