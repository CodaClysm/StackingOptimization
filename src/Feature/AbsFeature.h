#pragma once
#include <vector>
#include "../Genetic/State.h"

class AbsFeature
{
public:
	virtual vector<double> calculateFeature(vector<State> states) = 0;
	virtual ~AbsFeature() {};

};

