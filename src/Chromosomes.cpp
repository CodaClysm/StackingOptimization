#include "Chromosomes.h"

// Randomly initialize a chromosome based on the number of features
Chromosomes::Chromosomes()
{

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