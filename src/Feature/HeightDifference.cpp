#include "HeightDifference.h"
#include "MaxHeight.h"
#include <iostream>
double HeightDifference::calculateFeature(State s)
{
    auto sVector = s.state;
    MaxHeight m;
    double maxHeight = m.calculateFeature(s);
    int minHeight = 0;
    bool flag = false;
    for(int y = 0; y < sVector.size(); y++)
    {
        for(int z = 0; z < sVector[y].size(); z++)
        {
            for(int x = 0; x < sVector[y][z].size(); x++)
            {
                if(sVector[y][z][x])
                {
                    bool innerFlag = true;
                    for(int yy = y; yy < sVector.size(); yy++)
                    {
                        if(sVector[yy][z][x]) innerFlag = true;
                    }
                    if(innerFlag)
                    {
                        minHeight = y;
                    }
                    if(flag) break;
                }
            }
            if(flag) break;
        }
        if(flag) break;
    }

    return maxHeight - minHeight;
}