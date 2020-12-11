#include "Chromosomes.h"
#include "../Utils/Util.h"
#include "ControllerSettings.h"

// Randomly initialize a chromosome based on the number of features
Chromosomes::Chromosomes()
{
    int numFeatures = ControllerSettings::features.size();
    for(int i = 0; i < numFeatures; i++)
    {
        // Initialize weights to random number between -50 and 50
        weights.push_back(Util::randDouble(-50,50));
        // Initialize exponents to random number between 0 and 5
        exponents.push_back(Util::randDouble(0,5));
    }
    //initialize bias to random number between -100 and 100
    bias = Util::randDouble(-100,100);
    
}

Chromosomes::Chromosomes(vector<double> weights, vector<double> exponents, double bias)
{
    this->weights = weights;
    this->exponents = exponents;
    this->bias = bias;
}

vector<double> Chromosomes::getWeights()
{
    return this->weights;
}

vector<double> Chromosomes::getExponents()
{
    return this->exponents;
}

double Chromosomes::getBias()
{
    return bias;
}

string Chromosomes::toString()
{
    string s = "Weights: ";
    for(double d : weights)
    {
        s += to_string(d) + ", ";
    }
    s += "\nExponents: ";
    for(double d : exponents)
    {
        s+= to_string(d) + ", ";
    }
    s += "\nBias: " + to_string(bias) + "\n";
    return s;
}