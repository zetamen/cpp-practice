#pragma once

#include <vector>
#include "PointValue.h"

using std::vector;

class MapAlgorithm
{
public:
	MapAlgorithm() {}
	virtual void Apply(vector<vector<PointValue>>& matrix) = 0;
};

