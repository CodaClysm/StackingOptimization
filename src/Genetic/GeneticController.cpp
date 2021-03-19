#include <thread>
#include <iostream>
#include <future>
#include <math.h>
#include <chrono>
#include <fstream>
#include "GeneticController.h"
#include "ControllerSettings.h"
#include "../Utils/Util.h"
#include "../Utils/DebugLogger.h"
#include "../Utils/DataLogger.h"
using namespace std;

int GeneticController::generation = 1;
double GeneticController::mutationRate = .15;
double GeneticController::previousFitness = 0;
int GeneticController::fitnessStreak = 0;

void GeneticController::run(vector<AbsFeature*> features, Shape envShape,
                int numIndividuals, vector<Shape> possibleShapes, string file){

    DebugLogger::start(Level::ERROR);
    DataLogger::start();
    if(numIndividuals < 5)
    {
        DebugLogger::error("numIndividuals value selected too small. Must be > 4");
        exit(0);
    }

    // Set up global settings
    ControllerSettings::features = features;
    ControllerSettings::envShape = envShape;
    ControllerSettings::numIndividuals = numIndividuals;
    ControllerSettings::possibleShapes = possibleShapes;

    //Create initial population
    vector<Individual> population;
    if(file == "none")
    {
        cout << "starting new run\n";
        for(int i = 0; i < numIndividuals; i++)
        {
            population.push_back(Individual());
        }
    }
    else
    {
        population = getIndividualFromFile(file);
    }

    // infinite loop to run infinite generations. Each loop is one generation
    while(generation <= 500)
    {
        chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        string s = "Generation: ";
        s += to_string(generation) + " --- ";
        cout << s;
        DataLogger::log(s);

        // Loop through 3 iterations to get an average of individual performance
        vector<double> fitnessVector(population.size(), 0.0);
        int numIterations = 5;
        for(int iteration = 0; iteration < numIterations; iteration++)
        {
            //generate the new shape list
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

            //evaluate individuals
            for(int i = 0; i < population.size(); i++)
            {
                fitnessVector[i] += calculateFitness(population[i]);
            }
        }
        
        // divide all fitnesses by numIterations to get average
        for(int i = 0; i < fitnessVector.size(); i++)
        {
            fitnessVector[i] /= numIterations;
        }

        // From the next population through selection
        population = selection(population, fitnessVector);
        generation++;

        chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        cout << " --- exec Time: " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]";
        cout << " --- m/s: " << mutationRate << "/" << fitnessStreak << std::endl;

    }

    DebugLogger::close();
    DataLogger::close();
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

vector<Individual> GeneticController::selection(vector<Individual> oldPop, vector<double> fitnessVec){
    vector<Individual> newPop;
    vector<Individual> temp;
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
        if(j == 0)
        {
            //print the best result for the generation
            string s = "Best Utilization: " + to_string(max * 100) + "%";
            cout << s;
            s += "\n";
            DataLogger::log(s);
            DataLogger::log("Best state:\n");
            DataLogger::log(oldPop[maxIndex].getEnvironment().getCurrentState().toString_h());
            DataLogger::log("Current Best Chromosome:\n");
            DataLogger::log(oldPop[maxIndex].getChromosomes().toString());
            DataLogger::log("---------------------------------------------------------\n");
            DataLogger::log("All Chromosomes:\n");
            for(Individual i : oldPop)
            {
                DataLogger::log(i.getChromosomes().toString());
            }
            DataLogger::log("########################################################\n");
            
            //adjust mutation rate
            if(max > previousFitness)
            {
                fitnessStreak++;
            }
            else
            {
                fitnessStreak--;
            }
            previousFitness = max;

            if(fitnessStreak > 0)
            {
                mutationRate = .25 - (fitnessStreak*fitnessStreak*.01);
            }
            else
            {
                mutationRate = .25 + (fitnessStreak*fitnessStreak*.01);
            }
            if(mutationRate > .5)
            {
                mutationRate = .5;
            }
            if(mutationRate < .01)
            {
                mutationRate = .01;
            }
        }
        newPop.push_back(Individual(oldPop[maxIndex].getChromosomes()));
        temp.push_back(oldPop[maxIndex]);
        oldPop.erase(oldPop.begin() + maxIndex);
        fitnessVec.erase(fitnessVec.begin() + maxIndex);
    }

    //add the best performers back into the oldPop to be included for crossover
    for(Individual i : temp)
    {
        oldPop.push_back(i);
        fitnessVec.push_back(calculateFitness(i));
    }

    // Select individuals to perform crossover
    vector<Chromosomes> newChromosomes;
    while(newChromosomes.size() < ControllerSettings::numIndividuals - 3)
    {
        Individual ind1 = weightedSelect(oldPop, fitnessVec);
        Individual ind2 = weightedSelect(oldPop, fitnessVec);
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

Individual GeneticController::weightedSelect(vector<Individual> pop, vector<double> fitVec)
{
    double total = 0;
    for(double d : fitVec)
    {
        total += d;
    }
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
    DebugLogger::error("weighted Select in Genetic Controller shouldnt get here...");
    exit(0);
}

Individual GeneticController::ticketedSelect(vector<Individual> pop, vector<double> fitVec)
{
    vector<Individual> sortedInd;
    double smallestVal = fitVec[0];
    int smallestIndex = 0;
    int totalTickets = 0;
    for(int i = 0; i<fitVec.size(); i++)
    {
        totalTickets += i+1;
        for(int j = 0; j < fitVec.size(); j++)
        {
            if(fitVec[j] < smallestVal)
            {
                smallestVal = fitVec[j];
                smallestIndex = j;
            }
        }
        sortedInd.push_back(pop[smallestIndex]);
        pop.erase(pop.begin()+smallestIndex);
        fitVec.erase(fitVec.begin()+smallestIndex);
    }

    //get random ticket
    int randTicket = Util::randInt(1, totalTickets);
    int curTicket = 0;
    for(int i = 0; i < sortedInd.size(); i++)
    {
        curTicket += i+1;
        if(randTicket <= curTicket)
        {
            return sortedInd[i];
        }
    }
    DebugLogger::error("Ticketed Select in Genetic Controller shouldnt get here...");
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
    vector<double> newWeights;
    vector<double> newExponents;
    double newBias;
    for(int i = 0; i < c.getWeights().size(); i++)
    {
        double rand = Util::randDouble(0,1);
        if(rand < mutationRate)
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
        if(rand < mutationRate)
        {
            double normRand = Util::randNormal(0, 2);
            newExponents.push_back(abs(c.getExponents()[i] * normRand));
        }
        else
        {
            newExponents.push_back(c.getExponents()[i]);
        }
    }

    double rand = Util::randDouble(0,1);
    if(rand < mutationRate)
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

vector<Individual> GeneticController::getIndividualFromFile(string fileName)
{
    vector<Individual> population;
    fileName = "logs/"+fileName;
    cout << "continuing execution from " << fileName << endl;
    ifstream oldRun(fileName);
    if(!oldRun.good())
    {
        cout << "specified file does not exist. Exiting...\n";
        exit(0);
    }
    
    //parse file to get weights of old run. 
    string previousGenerationString2;
    string previousGenerationString;
    string generationString;
    string temp;
    
    while(getline(oldRun, temp))
    {
        if(temp.find("Generation") != -1)
        {
            previousGenerationString2 = previousGenerationString;
            previousGenerationString = generationString;
            generationString = temp + "\n";
            //copy over all of the logs to the new log file except for the latest run which will be re-run
            if(previousGenerationString != "")
            {
                DataLogger::log(previousGenerationString2);
            }
        }
        else
        {
            generationString += temp + "\n";
        }
    }
    string parseStr = previousGenerationString;

    //get generation
    temp = parseStr.substr(parseStr.find(" ") + 1);
    temp = temp.substr(0,temp.find(" "));
    generation = stoi(temp);

    //get weights, exponents, and bias
    temp = parseStr.substr(parseStr.find("All Chromosomes:")+17);

    bool end = false;
    while(!end)
    {
        string weightsStr = temp.substr(0, temp.find("Exponents: "));
        temp = temp.substr(weightsStr.length());

        string exponentsStr = temp.substr(0, temp.find("Bias: "));
        temp = temp.substr(exponentsStr.length());

        string biasStr;
        if(temp.find("Weights: ") != -1)
        {
            biasStr = temp.substr(0, temp.find("Weights: "));
        }
        else
        {
            biasStr = temp.substr(0, temp.find("#"));
            end = true;
        }
        temp = temp.substr(biasStr.length());

        //we now have strings with the chromosome information, parse these strings for values
        vector<double> fileWeights;
        vector<double> fileExponents;
        double fileBias;

        weightsStr = weightsStr.substr(weightsStr.find(" ") + 1);
        exponentsStr = exponentsStr.substr(exponentsStr.find(" ") + 1);
        biasStr = biasStr.substr(biasStr.find(" ") + 1);
        while(weightsStr.length() > 1)
        {
            string tempWeight = weightsStr.substr(0, weightsStr.find(","));
            weightsStr = weightsStr.substr(tempWeight.length() + 2);
            fileWeights.push_back(atof(tempWeight.c_str()));

            string tempExponent = exponentsStr.substr(0, exponentsStr.find(","));
            exponentsStr = exponentsStr.substr(tempExponent.length() + 2);
            fileExponents.push_back(atof(tempExponent.c_str()));
        }
        fileBias = atof(biasStr.c_str());
        
        //check that number of features is correct
        if(fileWeights.size() != ControllerSettings::features.size())
        {
            string error =  "feature mismatch: loaded file is for " + to_string(fileWeights.size()) +  " features.\n" 
                + "Controller is currently set to run with " + to_string(ControllerSettings::features.size()) + " features.\n";
            cout << "ERROR: " << error;
            DebugLogger::error(error);
            exit(0);
        }
        Chromosomes c(fileWeights, fileExponents, fileBias);
        population.push_back(Individual(c));
    }

    //check that the population size is correct.
    if(population.size() != ControllerSettings::numIndividuals)
    {
        string error = "population size mismatch: loaded file is for " + to_string(population.size()) + " individuals.\n"
            + "Controller is currently set to run with " + to_string(ControllerSettings::numIndividuals) + " individuals.\n";
            cout << "ERROR: " << error;
            DebugLogger::error(error);
            exit(0);
    }

    cout << "done parsing file. Resuming execution....\n";
    return population;
}