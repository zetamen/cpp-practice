#include "stdafx.h"
#include "Map.h"


Map::Map(vector<string> const& matrix)
	:m_matrix(HEIGHT, vector<Point>(WIDTH, Point::BLANK))
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

vector<vector<Point>> Map::GetMatrix() const
{
	return m_matrix;
}

Point Map::GetPoint(char const ch) const
{
	Point point;
	switch (ch)
	{
	case '#':
		point = Point::BLOCK;
		break;
	case 'O':
		point = Point::START;
		break;
	default:
		point = Point::BLANK;
		break;
	}
	return point;
}

char Map::GetChar(Point const point) const
{
	char ch;
	switch (point)
	{
	case Point::BLOCK:
		ch = '#';
		break;
	case Point::START:
		ch = 'O';
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

int Map::GetWidth() const
{
	return m_width;
}

int Map::GetHeight() const
{
	return m_height;
}

Map::~Map()
{
}
