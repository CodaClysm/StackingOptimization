#pragma once
#include <vector>
#include "AbsFeature.h"
#include "../Genetic/State.h"

class TransitionY : public AbsFeature
{
public:
	vector<double> calculateFeature(vector<State> s);
};

