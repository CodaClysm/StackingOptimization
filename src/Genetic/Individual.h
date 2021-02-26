#pragma once
#include <vector>
#include "Shape.h"
#include "../Feature/AbsFeature.h"
#include "Environment.h"
#include "Chromosomes.h"
#include "State.h"
using namespace std;
class Individual
{
private:
    static int counter;
    
    vector<double> calculateHeuristic(State s, vector<vector<double>> featureVals);
    State findBestPosition(vector<State> states);
    static vector<double> startFeatureCalculation(vector<State> states, int index);
    vector<int> shapesToPack;
    vector<AbsFeature*> features;
    Environment env;
    Chromosomes chromosomes;
public:
    int id;
    Individual(Chromosomes c);
    Individual();
    void start();
    Environment getEnvironment();
    Chromosomes getChromosomes();
};

