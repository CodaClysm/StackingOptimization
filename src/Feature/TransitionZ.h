#pragma once
#include "AbsFeature.h"
#include "../Genetic/State.h"

class TransitionZ : AbsFeature
{
public:
	double calculateFeature(State s);
};

