#pragma once
#include <vector>
#include "AbsFeature.h"
#include "Shape.h"
#include "Chromosomes.h"
#include "Individual.h"
using namespace std;
class GeneticController{

public:
    static void run(vector<AbsFeature> features, Shape envShape, int numIndividuals,
                vector<Shape> possibleShapes);

private:
    static vector<Shape> GenerateShapeOrder(vector<Shape> possibleShapes);
    static Individual startIndividual(Chromosomes c);
    static double calculateFitness(Individual i);
    static vector<Chromosomes> selection(vector<Individual> individuals);
    static Chromosomes crossover(Chromosomes c1, Chromosomes c2);
    static Chromosomes mutation(Chromosomes c);
};
