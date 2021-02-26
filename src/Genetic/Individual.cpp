#include <future>
#include <iostream>
#include <math.h>
#include "Individual.h"
#include "ControllerSettings.h"
#include "../Utils/Util.h"
#include "../Feature/AbsFeature.h"

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
    counter++;
    id = counter;
    chromosomes = c;
    shapesToPack = ControllerSettings::shapesToPack;
    features = ControllerSettings::features;
}

vector<double> Individual::calculateHeuristic(State s, vector<vector<double>> featureVals)
{
    vector<double> heuristicScores;
    for(int stateIndex = 0; stateIndex < featureVals[0].size(); stateIndex++)
    {
        double sum = 0;
        for(int featureIndex = 0; featureIndex < features.size(); featureIndex++)
        {
            sum += chromosomes.getWeights()[featureIndex]
                * pow(featureVals[featureIndex][stateIndex], chromosomes.getExponents()[featureIndex]);
        }
        sum += chromosomes.getBias();
        heuristicScores.push_back(sum);
    }
    return heuristicScores;
}

void Individual::start()
{
    // Bring shape set local
    shapesToPack = ControllerSettings::shapesToPack;
    vector<Shape> shapeSet = ControllerSettings::possibleShapes;
    int i = 1;
    bool useRandom = false;

    for(int s : shapesToPack)
    {
       
        // Get list of all possible places to put the new shape
        vector<State> possibleStates = env.getPossibleStates(shapeSet[s]);
        // If there is no place the put the shape, then the instance is over
        if(possibleStates.size() == 0)
        {
            break;
        }
        if(!useRandom)
        {
            // Find the best place to put the shape
            State bestState = findBestPosition(possibleStates);
            //cout << id << bestState.toString_h() << endl;
            env.updateState(bestState);
        }
        else
        {
            //update state with random state
            int randSelection = Util::randInt(0,possibleStates.size()-1);
            env.updateState(possibleStates[randSelection]);     
        } 
        i++;
    }
}

vector<double> Individual::startFeatureCalculation(vector<State> states, int index)
{
    return ControllerSettings::features[index]->calculateFeature(states);
}

State Individual::findBestPosition(vector<State> states)
{
    vector<vector<double>> featureVals;
    vector<future<vector<double>>> featureFuture;

    //start futures for each feature so that the GPU can start processing jobs for all features concurrently. 
    for(int i = 0; i < features.size(); i++)
    {
        featureFuture.push_back(async(startFeatureCalculation, states, i));
    }

    // Collect the futures
    for(int i = 0; i < featureFuture.size(); i++)
    {
        featureVals.push_back(featureFuture[i].get());
    }

    vector<double> stateHeuristicVector = calculateHeuristic(states[0], featureVals);
    State bestState = states[0];
    double bestVal = stateHeuristicVector[0];

    int i = 0;
    for(double val : stateHeuristicVector)
    {
        // cout << id <<"- stateProgress: " << i << "/" << states.size() << endl;
        if(val > bestVal)
        {
            bestState = states[i];
            bestVal = val;
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