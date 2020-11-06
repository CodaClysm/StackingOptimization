#pragma once
#include "State.h"
#include "Shape.h"
#include <vector>

using namespace std;

class AbsFeature
{
private:
	static int numIndividuals;
    static vector<AbsFeature> features;
    static Shape envShape;

};

