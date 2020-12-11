#pragma once
#include "AbsFeature.h"
#include "../Genetic/State.h"

class TransitionX : AbsFeature
{
public:
	double calculateFeature(State s);
};

