#include "Util.h"
#include <random>
double Util::randDouble(double min, double max)
{
    uniform_real_distribution<double> unif(min,max);
    default_random_engine re;
    double a_random_double = unif(re);
}

int Util::randInt(int min, int max)
{
    default_random_engine generator;
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

double Util::randNormal(double mean, double stdDev)
{
    default_random_engine generator;
    normal_distribution<double> distribution(mean, stdDev);
    return distribution(generator);
}