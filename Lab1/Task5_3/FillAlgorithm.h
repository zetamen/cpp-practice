#pragma once
#include "MapAlgorithm.h"
#include "Point.h"

class FillAlgorithm: public MapAlgorithm
{
public:
	FillAlgorithm();
	void Apply(vector<vector<PointValue>>& matrix);
	virtual ~FillAlgorithm();
private:
	vector<Point> GetStartPoints(vector<vector<PointValue>> const& matrix) const;
	void Fill(Point point, vector<vector<PointValue>>& matrix);
};

