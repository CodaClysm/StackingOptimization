#pragma once
#include "AbsFeature.h"
#include "../Genetic/State.h"

class MaxHeight : public AbsFeature
{
public:
	double calculateFeature(State s);
};

