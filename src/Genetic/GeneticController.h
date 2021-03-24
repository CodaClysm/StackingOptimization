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
                vector<Shape> possibleShapes, string file = "none");
    static void generateShapeFile(vector<Shape> possibleShapes, string fileName,Shape envShape);
    static vector<vector<int>> getShapeOrderFromFile(string fileName);

private:
    static vector<int> generateShapeOrder(vector<Shape> possibleShapes);
    static Individual startIndividual(Individual i);
    static double calculateFitness(Individual i);
    static vector<Individual> selection(vector<Individual> oldPop, vector<double> fitnessVector);
    static Chromosomes crossover(Chromosomes c1, Chromosomes c2);
    static Chromosomes crossover2(Chromosomes c1, Chromosomes c2);
    static Chromosomes mutation(Chromosomes c);
    static Individual weightedSelect(vector<Individual> pop, vector<double> fitVec);
    static Individual ticketedSelect(vector<Individual> pop, vector<double> fitVec);
    static vector<Individual> getIndividualFromFile(string fileName);
    static int streakSum();
    static int generation;
    static double mutationRate;
    static double previousFitness;
    static vector<int> fitnessStreak;
};
