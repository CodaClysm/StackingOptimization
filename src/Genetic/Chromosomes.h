#pragma once
#include <vector>
#include <string>

using namespace std;
class Chromosomes
{
private:
   vector<double> weights;
   double bias;
public:
    Chromosomes();
    Chromosomes(vector<double> weights, double bias);
    vector<double> getWeights();
    double getBias();
    string toString();
};

