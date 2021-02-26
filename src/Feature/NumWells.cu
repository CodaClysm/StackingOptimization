#include "NumWells.h"
#include <iostream>
#include <vector>
#include <math.h>

__device__ void getColumnHeight(int z, int x, State s, int &height)
{
    auto sVector = s.state;
    if(z < 0 || z >= sVector[0].size() || x < 0 || x >= sVector[0][0].size())
    {
        height = -1;
        return;
    }
    for(int y = sVector.size()-1; y >= 0; y--)
    {
        if(sVector[y][z][x])
        {
            height = y;
            return;
        }
    }
    height = -1;
}

__global__ void kernel(State *states, double *returnVals)
{
    double returnVal = 0;
    auto sVector = states[threadIdx.x]->state;
    auto s = states[threadIdx.x];
    for(int z = 0; z < sVector[0].size(); z++)
    {
        for(int x = 0; x < sVector[0][0].size(); x++)
        {
            int h = 0;
            int currentColHeight = 0;
            getColumnHeight(z, x, s, currentColHeight);
            vector<int> heights;
            getColumnHeight(z+1,x+1,s, h)
            heights.push_back(h);
            getColumnHeight(z+1,x,s, h)
            heights.push_back(h);
            getColumnHeight(z+1,x-1,s,h)
            heights.push_back(h);
            getColumnHeight(z,x+1,s,h)
            heights.push_back(h);
            getColumnHeight(z,x-1,s,h)
            heights.push_back(h);
            getColumnHeight(z-1,x+1,s,h)
            heights.push_back(h);
            getColumnHeight(z-1,x,s,h)
            heights.push_back(h);
            getColumnHeight(z-1,x-1,s,h)
            heights.push_back(h);
            for(int i : heights)
            {
                if(i != -1 && abs(currentColHeight - i) > 2)
                {
                    returnVal ++;
                }
            }
        }
    }
    
    returnVals[theadIdx.x] = returnVal;
}

double NumWells::calculateFeature(State s)
{
    //get size in bytes of needed memory space
    size_t stateSize = sizeof(State) * s.size();
    size_t returnSize = sizeof(double) * s.size();

    //setup pointers for host(CPU) and device(GPU)
    State *hostStates = &s[0];
    State *deviceStates;
    double *hostReturnVals = (double*)malloc(returnSize);
    double *deviceReturnVals;

    //allocate memory on the GPU
    cudaMalloc(&deviceStates, stateSize);
    cudaMalloc(&deviceReturnVals, returnSize);

    //copy memory from host to device
    cudaMemcpy(deviceStates, hostStates, stateSize, cudaMemcpyDeviceToHost);

    //run the GPU kernel
    kernel<<<1,s.size()>>>(deviceStates, deviceReturnVals);

    //copy memory back from device to host
    cudaMemcpy(hostReturnVals, deviceReturnVals, returnSize, cudaMemcpyHostToDevice);

    //create return vector from returned array
    vector<double> returnVec;
    for(int i = 0; i < s.size(); i++)
    {
        returnVec.push_back(hostReturnVals[i]);
    }

    //free up all memory from pointers
    free(hostStates);
    free(hostReturnVals);
    cudaFree(deviceStates);
    cudaFree(deviceReturnVals);

    return returnVec;
}