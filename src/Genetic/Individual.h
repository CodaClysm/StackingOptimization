#pragma once
#include <vector>
#include "Shape.h"
#include "Feature/AbsFeature.h"
#include "Environment.h"
#include "Chromosomes.h"
#include "State.h"
using namespace std;
class Individual
{
private:
    double calculateHeuristic(State s);
    State findBestPosition(vector<State> states);
    vector<int> shapesToPack; //grab this from the static class in the constructor
    vector<AbsFeature*> features;
    Environment env;
    Chromosomes chromosomes;
public:
    Individual(Chromosomes c);
    Individual();
    void start();
    Environment getEnvironment();
    Chromosomes getChromosomes();
};

