#pragma once
#include "AbsFeature.h"
#include "../Genetic/State.h"

class HeightDifference : public AbsFeature
{
public:
	double calculateFeature(State s);
};

