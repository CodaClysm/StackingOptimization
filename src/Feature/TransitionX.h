#pragma once
#include "AbsFeature.h"
#include "../Genetic/State.h"

class TransitionX : public AbsFeature
{
public:
	double calculateFeature(State s);
};

