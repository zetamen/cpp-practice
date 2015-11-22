#include "stdafx.h"
#include "Map.h"

Map::Map()
	:m_matrix(HEIGHT, vector<PointType>(WIDTH, PointType::BLANK))
{
}

vector<vector<PointType>> Map::GetMatrix() const
{
	return m_matrix;
}

void Map::SetPointType(int x, int y, PointType value)
{
	m_matrix[y][x] = value;
}

PointType Map::GetPointType(int x, int y) const
{
	return m_matrix[y][x];
}

Map::~Map()
{
}
