#include "stdafx.h"
#include "Map.h"

Map::Map()
	:m_matrix(HEIGHT, vector<PointValue>(WIDTH, PointValue::BLANK))
{
}

vector<vector<PointValue>> Map::GetMatrix() const
{
	return m_matrix;
}

void Map::SetPointValue(int x, int y, PointValue value)
{
	m_matrix[y][x] = value;
}

PointValue Map::GetPointValue(int x, int y) const
{
	return m_matrix[y][x];
}

Map::~Map()
{
}
