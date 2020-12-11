#pragma once
#include "../Genetic/State.h"

class AbsFeature
{
public:
	virtual double calculateFeature(State s) = 0;
};

