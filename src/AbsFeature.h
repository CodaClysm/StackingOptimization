#pragma once
#include "State.h"

class AbsFeature
{
public:
	virtual double calculateFeature(State s) = 0;
};

