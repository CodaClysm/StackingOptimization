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
#include "Feature/BadFeature.h"
#include "Feature/BadFeature2.h"
#include "Genetic/State.h"
#include "Utils/Util.h"

using namespace std;

int main()
{
	MaxHeight f1;
	NumHoles f2;
	HeightDifference f3;
	Smoothness f4;
	TransitionX f5;
	TransitionY f6;
	TransitionZ f7;
	MaxWellDepth f8;
	NumWells f9;
	BadFeature f10;
	BadFeature2 f11;

	vector<AbsFeature *> features;
	features.push_back(&f1);
	features.push_back(&f2);
	features.push_back(&f3);
	// features.push_back(&f4);
	features.push_back(&f5);
	features.push_back(&f6);
	features.push_back(&f7);
	// features.push_back(&f8);
	// features.push_back(&f9);
	// features.push_back(&f10);
	// features.push_back(&f11);

	Shape env(6, 6, 6);

	int numIndividuals = 10;

	//set1
	// Shape s1(2, 1, 1);
	// Shape s2(4, 1, 1);
	// Shape s3(2, 2, 2);
	// Shape s4(4, 4, 1);
	// Shape s5(4, 2, 2);
	// Shape s6(4, 3, 2);
	// Shape s7(3, 2, 2);

	//set2
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
	// shapes.push_back(s6);
	// shapes.push_back(s7);

	GeneticController::run(features, env, numIndividuals, shapes);

	return 1;
}