#pragma once
#include "AbsFeature.h"
#include "../Genetic/State.h"

class TransitionY : public AbsFeature
{
public:
	double calculateFeature(State s);
};

