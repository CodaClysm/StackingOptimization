#include "Individual.h"
#include "ControllerSettings.h"
#include <iostream>
#include <math.h>
using namespace std;

Individual::Individual(Chromosomes c)
{
    chromosomes = c;
    shapesToPack = ControllerSettings::shapesToPack;
    features = ControllerSettings::features;
}

double Individual::calculateHeuristic(State s)
{
    double returnVal = 0;
    for(int i = 0; i < features.size(); i++)
    {
        returnVal += chromosomes.getWeights()[i]
         * pow(features[i]->calculateFeature(s), chromosomes.getExponents()[i]);
    }
    returnVal += chromosomes.getBias();
    return returnVal;
}

void Individual::start()
{
    // Bring shape set local
    vector<Shape> shapeSet = ControllerSettings::possibleShapes;
    for(int i : shapesToPack)
    {
        // Get list of all possible places to put the new shape
        vector<State> possibleStates = env.getPossibleStates(shapeSet[i]);
        // If there is no place the put the shape, then the instance is over
        if(possibleStates.size() == 0)
        {
            break;
        }

        // Find the best place to put the shape
        State bestState = findBestPosition(possibleStates);
        env.updateState(bestState);
    }
}

State Individual::findBestPosition(vector<State> states)
{
    State bestState = states[0];
    double bestStateVal = calculateHeuristic(states[0]);

    for(State s : states)
    {
        double val = calculateHeuristic(s);
        if(val > bestStateVal)
        {
            bestState = s;
            bestStateVal = val;
        }
    }

    return bestState;
}

Environment Individual::getEnvironment()
{
    return env;
}