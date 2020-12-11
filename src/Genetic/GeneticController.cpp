#include "GeneticController.h"
#include "ControllerSettings.h"
#include "Util.h"
#include "Logger.h"
#include <thread>
#include <future>
using namespace std;

void GeneticController::run(vector<AbsFeature*> features, Shape envShape,
                int numIndividuals, vector<Shape> possibleShapes){

    
    if(numIndividuals < 5)
    {
        Logger::error("numIndividuals value selected too small. Must be > 4");
        exit(0);
    }

    // Set up global settings
    ControllerSettings::features = features;
    ControllerSettings::envShape = envShape;
    ControllerSettings::numIndividuals = numIndividuals;
    ControllerSettings::possibleShapes = possibleShapes;


    //Create initial population
    vector<Individual> population;
    for(int i = 0; i < numIndividuals; i++)
    {
        population.push_back(Individual());
    }

    // infinite loop to run infinite generations. Each loop is one generation
    while(1)
    {
        ControllerSettings::shapesToPack = generateShapeOrder(possibleShapes);
        vector<future<Individual>> futures;

        // Start to process each individual as a future
        for(Individual i : population)
        {
            futures.push_back(async(startIndividual, i));
        }

        // Wait for all of them to finish
        for(int i = 0; i < population.size(); i++)
        {
            population[i] = futures[i].get();
        }

        // From the next population through selection
        population = selection(population);
    }
}

vector<int> GeneticController::generateShapeOrder(vector<Shape> possibleShapes){
    int environmentVolume = ControllerSettings::envShape.getVolume();
    int numRandomShapes = ControllerSettings::possibleShapes.size();
    int accumulatedVolume = 0;
    vector<int> newShapes;
    while (accumulatedVolume < environmentVolume)
    {
        int rand = Util::randInt(0, numRandomShapes-1);
        newShapes.push_back(rand);
        accumulatedVolume += ControllerSettings::possibleShapes[rand].getVolume();
    }
    return newShapes;
}

Individual GeneticController::startIndividual(Individual i){
    i.start();
    return i;
}

double GeneticController::calculateFitness(Individual i){
    Environment e = i.getEnvironment();
    State s = e.getCurrentState();
    return s.getUtilization();
}

vector<Individual> GeneticController::selection(vector<Individual> oldPop){
    vector<Individual> newPop;

    // Get fitness of each individual
    vector<double> fitnessVec;
    for(Individual i : oldPop)
    {
        fitnessVec.push_back(calculateFitness(i));
    }

    //Reserve the best three performing individuals for the next population
    for(int j = 0; j < 3; j++)
    {
        double max = 0;
        int maxIndex = -1;
        for(int i = 0; i < oldPop.size(); i++)
        {
            if(fitnessVec[i] > max)
            {
                max = fitnessVec[i];
                maxIndex = i;
            }
        }
        newPop.push_back(oldPop[maxIndex]);
        oldPop.erase(oldPop.begin() + maxIndex);
        fitnessVec.erase(fitnessVec.begin() + maxIndex);
    }

    //add the best performers back into the vectors
    for(Individual i : newPop)
    {
        oldPop.push_back(i);
        fitnessVec.push_back(calculateFitness(i));
    }

    // Select individuals to perform crossover
    double totalFitness = 0;
    for(double d : fitnessVec)
    {
        totalFitness += d;
    }

    vector<Chromosomes> newChromosomes;
    while(newChromosomes.size() < ControllerSettings::numIndividuals - 3)
    {
        Individual ind1 = weightedSelect(totalFitness, oldPop, fitnessVec);
        Individual ind2 = weightedSelect(totalFitness, oldPop, fitnessVec);
        newChromosomes.push_back(crossover2(ind1.getChromosomes(), ind2.getChromosomes()));
    }

    for(int i = 0; i < newChromosomes.size(); i++)
    {
        newChromosomes[i] = mutation(newChromosomes[i]);
    }

    for(Chromosomes c : newChromosomes)
    {
        newPop.push_back(Individual(c));
    }
    return newPop;
}

Individual GeneticController::weightedSelect(double total, vector<Individual> pop, vector<double> fitVec)
{
    double rand = Util::randDouble(0, total);
    int i = 0;
    double counter = 0;
    while(counter <= rand)
    {
        if(counter <= rand && rand <= counter + fitVec[i])
        {
            return pop[i];
        }
        counter += fitVec[i];
        i++;
    }
    Logger::error("weighted Select in Genetic Controller shouldnt get here...");
    exit(0);
}

Chromosomes GeneticController::crossover(Chromosomes c1, Chromosomes c2)
{
    int numFeatures = ControllerSettings::features.size();
    int split1 = Util::randInt(1, numFeatures/2);
    int split2 = Util::randInt((numFeatures/2) + 1, numFeatures);

    vector<double> newWeights;
    vector<double> newExponents;
    double newBias;
    for(int i = 0; i < c1.getWeights().size(); i++)
    {
        if(i <= split1)
        {
            newWeights.push_back(c1.getWeights()[i]);
            newExponents.push_back(c1.getExponents()[i]);
        }
        else if(i <= split2)
        {
            newWeights.push_back(c2.getWeights()[i]);
            newExponents.push_back(c2.getExponents()[i]);
        }
        else
        {
            newWeights.push_back(c1.getWeights()[i]);
            newExponents.push_back(c1.getExponents()[i]);
        }
    }
    int coinFlip = Util::randInt(0,1);
    if(coinFlip == 0)
    {
        newBias = c1.getBias();
    }
    else
    {
        newBias = c2.getBias();
    }
    return Chromosomes(newWeights, newExponents, newBias);
}

Chromosomes GeneticController::crossover2(Chromosomes c1, Chromosomes c2)
{
    vector<double> newWeights;
    vector<double> newExponents;
    double newBias;
    for(int i = 0; i < c1.getWeights().size(); i++)
    {
        newWeights.push_back((c1.getWeights()[i] + c2.getWeights()[i]) / 2);
        newExponents.push_back((c1.getExponents()[i] + c2.getExponents()[i]) / 2);
    }
    newBias = (c1.getBias() + c2.getBias()) /2;
    return Chromosomes(newWeights, newExponents, newBias);
}

Chromosomes GeneticController::mutation(Chromosomes c)
{
    double mutationProbability = .15;
     
    vector<double> newWeights;
    vector<double> newExponents;
    double newBias;
    for(int i = 0; i < c.getWeights().size(); i++)
    {
        double rand = Util::randDouble(0,1);
        if(rand < mutationProbability)
        {
            double normRand = Util::randNormal(0, 2);
            newWeights.push_back(c.getWeights()[i] * normRand);
        }
        else
        {
            newWeights.push_back(c.getWeights()[i]);
        }
    }

    for(int i = 0; i < c.getWeights().size(); i++)
    {
        double rand = Util::randDouble(0,1);
        if(rand < mutationProbability)
        {
            double normRand = Util::randNormal(0, 2);
            newExponents.push_back(c.getExponents()[i] * normRand);
        }
        else
        {
            newExponents.push_back(c.getExponents()[i]);
        }
    }

    double rand = Util::randDouble(0,1);
    if(rand < mutationProbability)
    {
        double normRand = Util::randNormal(0, 2);
        newBias = c.getBias() * normRand;
    }
    else
    {
        newBias = c.getBias();
    }
    return Chromosomes(newWeights, newExponents, newBias);
}