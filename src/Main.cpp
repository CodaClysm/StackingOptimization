#include <iostream>
#include <vector>
#include "Genetic/GeneticController.h"
#include "Feature/MaxHeight.h"
#include "Feature/NumHoles.h"
#include "Feature/HeightDifference.h"
#include "Feature/Smoothness.h"
#include "Feature/TransitionX.h"
#include "Feature/TransitionY.h"
#include "Feature/TransitionZ.h"
#include "Feature/MaxWellDepth.h"
#include "Feature/NumWells.h"
#include "Genetic/State.h"
#include "Utils/Util.h"

using namespace std;


int main() {
	MaxHeight f1;
	NumHoles f2;
	HeightDifference f3;
	Smoothness f4;
	TransitionX f5;
	TransitionY f6;
	TransitionZ f7;
	MaxWellDepth f8;
	NumWells f9;

	vector<AbsFeature*> features;
	features.push_back(&f1);
	features.push_back(&f2);
	features.push_back(&f3);
	features.push_back(&f4);
	features.push_back(&f5);
	features.push_back(&f6);
	features.push_back(&f7);
	features.push_back(&f8);
	features.push_back(&f9);

	Shape env(7, 10, 5);

	int numIndividuals = 10;

	Shape s1(2,2,2);
	Shape s2(1,5,1);
	Shape s3(1,3,3);
	Shape s4(2,3,4);
	Shape s5(4,2,1);

	vector<Shape> shapes;
	shapes.push_back(s1);
	shapes.push_back(s2);
	shapes.push_back(s3);
	shapes.push_back(s4);
	shapes.push_back(s5);
	
	GeneticController::run(features, env,  numIndividuals, shapes);

	return 1;
}