#include "TransitionY.h"
#include <iostream>
#include <vector>
#include <math.h>
double TransitionY::calculateFeature(State s)
{
    double returnVal = 0;
    auto sVector = s.state;

    /*
    (if two horizontally adjacent cells are not both occupied or free, they count as a transition cell)
    Here, a transition occurs for each edge of an occupied cell that is adjacent to an unoccupied cell along the X axis. The walls count as occupied cells. 
    */

    for(int y = 0; y<sVector.size(); y++)
    {
        for(int z = 0; z < sVector[0].size(); z++)
        {
            for(int x = 0; x < sVector[0][0].size(); x++)
            {
                if(!sVector[y][z][x])
                {
                    if(y-1 < 0)
                    {
                        returnVal++;
                        if(sVector[y+1][z][x])
                        {
                            returnVal++;
                        }
                    }
                    else if(y+1 >= sVector.size())
                    {
                        returnVal++;
                        if(sVector[y-1][z][x])
                        {
                            returnVal++;
                        }
                    }
                    else
                    {
                        if(sVector[y-1][z][x])
                        {
                            returnVal++;
                        }
                        if(sVector[y+1][z][x])
                        {
                            returnVal++;
                        }
                    }
                }              
            }
        }
    }
    return returnVal;
}