#pragma once
#include "AbsFeature.h"
#include "../Genetic/State.h"

class NumWells : public AbsFeature
{
public:
	double calculateFeature(State s);
private:
	int getColumnHeight(int z, int x, State s);
};

