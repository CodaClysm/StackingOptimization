#pragma once
#include "AbsFeature.h"
#include "../Genetic/State.h"

class TransitionZ : public AbsFeature
{
public:
	double calculateFeature(State s);
};

