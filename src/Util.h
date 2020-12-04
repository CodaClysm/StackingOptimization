#pragma once
using namespace std;
class Util
{
public:
    Util();
    static double randDouble(double min, double max);
    static int randInt(int min, int max);
    static double randNormal(double mean, double stdDev);
};

