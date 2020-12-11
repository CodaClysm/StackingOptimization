#pragma once
#include "AbsFeature.h"
#include "../Genetic/State.h"

class HeightDifference : AbsFeature
{
public:
	double calculateFeature(State s);
};

