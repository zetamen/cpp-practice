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
		if (matrix[p.y][p.x] == PointValue::BLANK)
		{
			matrix[p.y][p.x] = PointValue::FILLED;
		}
		if ((p.x > 0) && (matrix[p.y][p.x - 1] == PointValue::BLANK))
		{
			Point point(p.x - 1, p.y);
			points.push_back(point);
		}
		if ((p.x < Map::WIDTH - 1) && (matrix[p.y][p.x + 1] == PointValue::BLANK))
		{
			Point point(p.x + 1, p.y);
			points.push_back(point);
		}
		if ((p.y > 0) && (matrix[p.y - 1][p.x] == PointValue::BLANK))
		{
			Point point(p.x, p.y - 1);
			points.push_back(point);
		}
		if ((p.y < Map::HEIGHT - 1) && (matrix[p.y + 1][p.x] == PointValue::BLANK))
		{
			Point point(p.x, p.y + 1);
			points.push_back(point);
		}
	}
}

FillAlgorithm::~FillAlgorithm()
{
}
