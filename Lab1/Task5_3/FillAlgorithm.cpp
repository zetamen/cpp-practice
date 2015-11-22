#include "stdafx.h"
#include "FillAlgorithm.h"
#include "Map.h"

#include <iostream>

FillAlgorithm::FillAlgorithm()
{
}

void FillAlgorithm::Apply(vector<vector<PointValue>>& matrix)
{
	vector<Point> startPoints = GetStartPoints(matrix);
	int size = startPoints.size();
	for (int i = 0; i < size; ++i)
	{
		Fill(startPoints[i], matrix);
	}
}

vector<Point> FillAlgorithm::GetStartPoints(vector<vector<PointValue>> const& matrix) const
{
	vector<Point> startPoints;
	for (int y = 0; y < Map::HEIGHT; ++y)
	{
		for (int x = 0; x < Map::WIDTH; ++x)
		{
			if (matrix[y][x] == PointValue::START)
			{
				Point point(x, y);
				startPoints.push_back(point);
			}
		}
	}
	return startPoints;
}

void FillAlgorithm::Fill(Point point, vector<vector<PointValue>>& matrix)
{
	vector<Point> points(1, point);
	while (!points.empty())
	{
		Point p = points.back();
		points.pop_back();
		if ((p.x > 0) && (matrix[p.y][p.x - 1] == PointValue::BLANK))
		{
			matrix[p.y][p.x - 1] = PointValue::FILLED;
			points.emplace_back(p.x - 1, p.y);
		}
		if ((p.x < Map::WIDTH - 1) && (matrix[p.y][p.x + 1] == PointValue::BLANK))
		{
			matrix[p.y][p.x + 1] = PointValue::FILLED;
			points.emplace_back(p.x + 1, p.y);
		}
		if ((p.y > 0) && (matrix[p.y - 1][p.x] == PointValue::BLANK))
		{
			matrix[p.y - 1][p.x] = PointValue::FILLED;
			points.emplace_back(p.x, p.y - 1);
		}
		if ((p.y < Map::HEIGHT - 1) && (matrix[p.y + 1][p.x] == PointValue::BLANK))
		{
			matrix[p.y + 1][p.x] = PointValue::FILLED;
			points.emplace_back(p.x, p.y + 1);
		}
	}
}

FillAlgorithm::~FillAlgorithm()
{
}
