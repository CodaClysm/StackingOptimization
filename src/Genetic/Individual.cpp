#include "Individual.h"
#include "ControllerSettings.h"
#include <iostream>
#include <math.h>

#include "../Feature/MaxHeight.h"
#include "../Feature/NumHoles.h"
#include "../Feature/HeightDifference.h"
#include "../Feature/Smoothness.h"
#include "../Feature/TransitionX.h"
#include "../Feature/TransitionY.h"
#include "../Feature/TransitionZ.h"
#include "../Feature/MaxWellDepth.h"
#include "../Feature/NumWells.h"

using namespace std;

int Individual::counter = 0;

Individual::Individual()
{
    counter++;
    id = counter;
    chromosomes = Chromosomes();
    features = ControllerSettings::features;
}

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
    shapesToPack = ControllerSettings::shapesToPack;
    vector<Shape> shapeSet = ControllerSettings::possibleShapes;
    for(int i = 0; i < shapesToPack.size(); i++)
    {
        cout << id <<"- ShapeProgress: " << i << "/" << shapesToPack.size() << endl;
        // Get list of all possible places to put the new shape
        vector<State> possibleStates = env.getPossibleStates(shapeSet[shapesToPack[i]]);
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
    int i = 0;
    for(State s : states)
    {
        //cout << id <<"- stateProgress: " << i << "/" << states.size() << endl;
        double val = calculateHeuristic(s);
        if(val > bestStateVal)
        {
            bestState = s;
            bestStateVal = val;
        }
        i++;
    }

    return bestState;
}

Environment Individual::getEnvironment()
{
    return env;
}

Chromosomes Individual::getChromosomes()
{
    return chromosomes;
}