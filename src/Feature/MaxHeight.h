#pragma once
#include "AbsFeature.h"
#include "../Genetic/State.h"

class MaxHeight : AbsFeature
{
public:
	double calculateFeature(State s);
};

