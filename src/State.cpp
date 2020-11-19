#include "State.h"
#include <iostream>

/*
* Function: State ctor
* Parameters: 
*   int x: x dimension of the new state
*   int y: y dimension of the new state
*   int z: z dimension of the new state
* description: create an empty state with the given dimensions
*/
State::State(int x, int y, int z)
{
    for(int i = 0; i < x; i++)
    {
        vector<vector<bool>> temp;
        for(int j = 0; j < y; j++)
        {
            temp.push_back(vector<bool>(z, false));
        }
        state.push_back(temp);
    }
}

/*
* Function: print
* Parameters:
* description: prints each horizontal layer of the state from botom to top
*/
void State::print()
{
    for(int i = 0; i < state.size(); i++)
    {
        for(int j = 0; j < state[i].size(); j++)
        {
            for(int k = 0; k < state[i][j].size(); k++)
            {
                cout << state[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}