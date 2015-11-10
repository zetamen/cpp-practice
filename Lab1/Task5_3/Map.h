#pragma once

#include <vector>
#include <memory>
#include "PointValue.h"
#include "MapAlgorithm.h"

using namespace std;

class Map
{
public:
	Map();
	vector<vector<PointValue>> GetMatrix() const;
	void SetPointValue(int x, int y, PointValue value);
	PointValue GetPointValue(int x, int y) const;
	void ApplyAlgorithm(shared_ptr<MapAlgorithm> algorithm);
	~Map();

	static const int WIDTH = 100;
	static const int HEIGHT = 30;
private:
	vector<vector<PointValue>> m_matrix;
};

