#include "MaxHeight.h"

double MaxHeight::calculateFeature(State s)
{
    double returnVal = 0;
    auto sVector = s.state;
    bool flag = false;
    for(int y = sVector.size()-1; y >= 0; y--)
    {
        for(int z = 0; z < sVector[y].size(); z++)
        {
            for(int x = 0; x < sVector[y][z].size(); x++)
            {
                if(sVector[y][z][x])
                {
                    returnVal = y;
                    flag = true;
                    break;
                }
            }
            if(flag) break;
        }
        if(flag) break;
    }
    return returnVal;
}