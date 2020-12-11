#include "NumHoles.h"
#include <iostream>
double NumHoles::calculateFeature(State s)
{
    double returnVal = 0;
    auto sVector = s.state;

    for(int z = 0; z < sVector[0].size(); z++)
    {
        for(int x = 0; x < sVector[0][0].size(); x++)
        {
            bool canBeHole = false;
            for(int y = 0; y < sVector.size(); y++)
            {
                if(!sVector[y][z][x])
                {
                    canBeHole = true;
                }
                else if (sVector[y][z][x] && canBeHole)
                {
                    returnVal++;
                    canBeHole = false;
                }
            }
            
        }
    }

    return returnVal;
}