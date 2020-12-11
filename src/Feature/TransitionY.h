#pragma once
#include "AbsFeature.h"
#include "../Genetic/State.h"

class TransitionY : AbsFeature
{
public:
	double calculateFeature(State s);
};

