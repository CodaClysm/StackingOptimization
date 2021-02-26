#pragma once
#include <vector>
#include "AbsFeature.h"
#include "../Genetic/State.h"

class TransitionX : public AbsFeature
{
public:
	vector<double> calculateFeature(vector<State> s);
};

