#pragma once

#include <vector>
#include <memory>
#include "PointValue.h"

using namespace std;

class Map
{
public:
	Map();
	vector<vector<PointValue>> GetMatrix() const;
	void SetPointValue(int x, int y, PointValue value);
	PointValue GetPointValue(int x, int y) const;
	~Map();

	static const int WIDTH = 100;
	static const int HEIGHT = 30;
private:
	vector<vector<PointValue>> m_matrix;
};

