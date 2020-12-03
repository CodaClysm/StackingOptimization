#pragma once
#include "State.h"
#include "Shape.h"
#include "AbsFeature.h"
#include <vector>

using namespace std;

class ControllerSettings
{
public:
	static int numIndividuals;
    static vector<AbsFeature*> features;
    static Shape envShape;
    static vector<Shape> possibleShapes;
    static vector<int> shapesToPack;
};
