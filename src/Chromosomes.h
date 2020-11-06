#pragma once
#include <vector>

using namespace std;
class Chromosomes
{
private:
   vector<double> weights;
   vector<double> exponents;
   double bias;
public:
    Chromosomes();
    Chromosomes(vector<double> weights, vector<double> exponents, double bias);
    vector<double> getWeights();
    vector<double> getExponents();
    double getBias();
};

