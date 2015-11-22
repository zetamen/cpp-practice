#pragma once

#include <vector>
#include <memory>
#include "PointType.h"

using namespace std;

class Map
{
public:
	Map();
	vector<vector<PointType>> GetMatrix() const;
	void SetPointType(int x, int y, PointType value);
	PointType GetPointType(int x, int y) const;
	~Map();

	static const int WIDTH = 100;
	static const int HEIGHT = 30;
private:
	vector<vector<PointType>> m_matrix;
};

