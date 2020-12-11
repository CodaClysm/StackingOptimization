#include "Util.h"
#include <random>
double Util::randDouble(double min, double max)
{
    //seed
	random_device rd;
    mt19937 mt(rd());
    
    uniform_real_distribution<double> unif(min,max);
    return unif(rd);
}

int Util::randInt(int min, int max)
{
    //seed
	random_device rd;
    mt19937 mt(rd());
    
    uniform_int_distribution<int> distribution(min, max);
    return distribution(mt);
}

double Util::randNormal(double mean, double stdDev)
{
    //seed
	random_device rd;
    mt19937 mt(rd());    
    normal_distribution<double> distribution(mean, stdDev);
    return distribution(rd);
}