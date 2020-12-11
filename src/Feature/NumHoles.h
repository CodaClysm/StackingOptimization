#pragma once
#include "AbsFeature.h"
#include "../Genetic/State.h"

class NumHoles : public AbsFeature
{
public:
	double calculateFeature(State s);
};

