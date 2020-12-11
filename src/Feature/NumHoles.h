#pragma once
#include "AbsFeature.h"
#include "../Genetic/State.h"

class NumHoles : AbsFeature
{
public:
	double calculateFeature(State s);
};

