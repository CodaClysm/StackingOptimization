#include "MaxWellDepth.h"
#include <iostream>
#include <vector>
#include <math.h>
double MaxWellDepth::calculateFeature(State s)
{
    double returnVal = 0;
    auto sVector = s.state;


    for(int z = 0; z < sVector[0].size(); z++)
    {
        for(int x = 0; x < sVector[0][0].size(); z++)
        {
            int currentColHeight = getColumnHeight(z, x, s);
            vector<int> heights;
            heights.push_back(getColumnHeight(z+1,x+1,s));
            heights.push_back(getColumnHeight(z+1,x,s));
            heights.push_back(getColumnHeight(z+1,x-1,s));
            heights.push_back(getColumnHeight(z,x+1,s));
            heights.push_back(getColumnHeight(z,x-1,s));
            heights.push_back(getColumnHeight(z-1,x+1,s));
            heights.push_back(getColumnHeight(z-1,x,s));
            heights.push_back(getColumnHeight(z-1,x-1,s));
            for(int i : heights)
            {
                if(i != -1 && abs(currentColHeight - i) > returnVal)
                {
                    returnVal = abs(currentColHeight - i);
                }
            }
        }
    }
    
    return returnVal;
}

int MaxWellDepth::getColumnHeight(int z, int x, State s)
{
    auto sVector = s.state;
    if(z < 0 || z >= sVector[0].size() || x < 0 || x >= sVector[0][0].size())
    {
        return -1;
    }
    for(int y = sVector.size()-1; y >= 0; y--)
    {
        if(sVector[y][z][x])
        {
            return y;
        }
    }
    return -1;
}