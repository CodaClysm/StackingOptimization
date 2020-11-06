#include "Individual.h"

Individual::Individual(Chromosomes c)
{
    chromosomes = c;
}

double Individual::calculateHeuristic(State s)
{

}

Environment Individual::getEnvironment()
{
    return env;
}