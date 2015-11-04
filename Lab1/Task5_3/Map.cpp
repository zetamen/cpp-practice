#include "stdafx.h"
#include "Map.h"

Map::Map(vector<string> const& matrix)
	:m_matrix(HEIGHT, vector<PointValue>(WIDTH, PointValue::BLANK))
{
	int height = matrix.size(),
		width;
	for (int j = 0; j < height; ++j)
	{
		width = matrix[j].size();
		for (int i = 0; i < width; ++i)
		{
			m_matrix[j][i] = GetPoint(matrix[j][i]);
		}
	}
}

vector<vector<PointValue>> Map::GetMatrix() const
{
	return m_matrix;
}

PointValue Map::GetPoint(char const ch) const
{
	PointValue point;
	switch (ch)
	{
	case '#':
		point = PointValue::BLOCK;
		break;
	case 'O':
		point = PointValue::START;
		break;
	case '.':
		point = PointValue::FILLED;
		break;
	default:
		point = PointValue::BLANK;
		break;
	}
	return point;
}

char Map::GetChar(PointValue const point) const
{
	char ch;
	switch (point)
	{
	case PointValue::BLOCK:
		ch = '#';
		break;
	case PointValue::START:
		ch = 'O';
		break;
	case PointValue::FILLED:
		ch = '.';
		break;
	default:
		ch = ' ';
		break;
	}
	return ch;
}

char Map::GetCharValue(int x, int y) const
{
	return GetChar(m_matrix[y][x]);
}

void Map::ApplyAlgorithm(shared_ptr<MapAlgorithm> algorithm)
{
	algorithm.get()->Apply(m_matrix);
}

Map::~Map()
{
}
