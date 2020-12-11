#pragma once
#include <vector>
#include "../Feature/AbsFeature.h"
#include "Shape.h"
#include "Chromosomes.h"
#include "Individual.h"
using namespace std;

class GeneticController{
public:
    static void run(vector<AbsFeature*> features, Shape envShape, int numIndividuals,
                vector<Shape> possibleShapes);

private:
    static vector<int> generateShapeOrder(vector<Shape> possibleShapes);
    static Individual startIndividual(Individual i);
    static double calculateFitness(Individual i);
    static vector<Individual> selection(vector<Individual> oldPop);
    static Chromosomes crossover(Chromosomes c1, Chromosomes c2);
    static Chromosomes crossover2(Chromosomes c1, Chromosomes c2);
    static Chromosomes mutation(Chromosomes c);
    static Individual weightedSelect(double total, vector<Individual> pop, vector<double> fitVec);
};
