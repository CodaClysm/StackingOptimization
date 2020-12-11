#include "HeightDifference.h"
#include "MaxHeight.h"
#include <iostream>
double HeightDifference::calculateFeature(State s)
{
    double returnVal = 0;
    auto sVector = s.state;
    MaxHeight m;
    double maxHeight = m.calculateFeature(s);
    int minHeight = 0;
    for(int y = 0; y < sVector.size(); y++)
    {
        for(int z = 0; z < sVector[y].size(); z++)
        {
            for(int x = 0; x < sVector[y][z].size(); x++)
            {
                if(sVector[y][z][x])
                {
                    minHeight = y;
                    break;
                }
            }
        }
    }

    return maxHeight - minHeight;
}