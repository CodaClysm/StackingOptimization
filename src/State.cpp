#include "State.h"
#include "ControllerSettings.h"
#include <iostream>

/*
* Function: State ctor
* Parameters: 
*   int x: x dimension of the new state
*   int y: y dimension of the new state
*   int z: z dimension of the new state
* Description: create an empty state with the given dimensions
*/
State::State()
{
    for(int i = 0; i < ControllerSettings::envShape.getY(); i++)
    {
        vector<vector<bool>> temp;
        for(int j = 0; j < ControllerSettings::envShape.getZ(); j++)
        {
            temp.push_back(vector<bool>(ControllerSettings::envShape.getX(), false));
        }
        state.push_back(temp);
    }
}

/*
* Function: toString
* Parameters:
* Description: generates a string to represent the 3d state in vertical format. 
*/
string State::toString()
{
    string returnString = "\n";

    for(int i = 0; i < state.size(); i++)
    {
        for(int j = 0; j < state[1].size(); j++)
        {
            for(int k = 0; k < state[i][j].size(); k++)
            {
                returnString += to_string(state[i][j][k]);
                returnString += " ";
            }
            returnString += "\n";
        }
        returnString += "\n";
    }
    return returnString;
}
/*
* Function: toString_h
* Parameters:
* Description: generates a string to represent the 3d state in horizontal format. 
*/
string State::toString_h()
{
    string returnString = "\n";
    for(int j = 0; j < state[1].size(); j++)
    {
        for(int i = 0; i < state.size(); i++)
        {
            for(int k = 0; k < state[i][j].size(); k++)
            {
                returnString += to_string(state[i][j][k]);
                returnString += " ";
            }
            returnString += " | ";
        }
        returnString += "\n";
    }
    return returnString;
}

