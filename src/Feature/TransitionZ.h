#pragma once
#include <vector>
#include "AbsFeature.h"
#include "../Genetic/State.h"

class TransitionZ : public AbsFeature
{
public:
	vector<double> calculateFeature(vector<State> s);
};

