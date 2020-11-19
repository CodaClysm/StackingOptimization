#include "Individual.h"
#include <iostream>
using namespace std;

Individual::Individual(Chromosomes c)
{
    chromosomes = c;
}

double Individual::calculateHeuristic(State s)
{
    //placeholder to get it to compile
    cout << "NOT IMPlEMENTED: indiviidual::calculateHeuristic\n";
    return 5.0;
}

Environment Individual::getEnvironment()
{
    return env;
}