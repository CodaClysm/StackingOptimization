#include "NumHoles.h"
#include <iostream>

__global__ void kernel(State *states, double *returnVals)
{
    double returnVal = 0;
    auto sVector = states[threadIdx.x]->state;
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
    
    returnVals[theadIdx.x] = returnVal;
}

vector<double> NumHoles::calculateFeature(vector<State> s)
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