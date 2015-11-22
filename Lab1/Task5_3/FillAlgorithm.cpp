#include "stdafx.h"
#include "FillAlgorithm.h"
#include "Map.h"
#include <iostream>

void FillAlgorithm::Apply(Map* map)
{
	vector<Point> startPoints = GetStartPoints(map);
	int size = startPoints.size();
	for (int i = 0; i < size; ++i)
	{
		Fill(startPoints[i], map);
	}
}

vector<Point> FillAlgorithm::GetStartPoints(Map const* map)
{
	vector<Point> startPoints;
	for (int y = 0; y < Map::HEIGHT; ++y)
	{
		for (int x = 0; x < Map::WIDTH; ++x)
		{
			if (map->GetPointValue(x, y) == PointValue::START)
			{
				startPoints.emplace_back(x, y);
			}
		}
	}
	return startPoints;
}

void FillAlgorithm::Fill(Point point, Map* const map)
{
	vector<Point> points(1, point);
	while (!points.empty())
	{
		Point p = points.back();
		points.pop_back();
		if ((p.x > 0) && (map->GetPointValue(p.x - 1, p.y) == PointValue::BLANK))
		{
			map->SetPointValue(p.x - 1, p.y, PointValue::FILLED);
			points.emplace_back(p.x - 1, p.y);
		}
		if ((p.x < Map::WIDTH - 1) && (map->GetPointValue(p.x + 1, p.y) == PointValue::BLANK))
		{
			map->SetPointValue(p.x + 1, p.y, PointValue::FILLED);
			points.emplace_back(p.x + 1, p.y);
		}
		if ((p.y > 0) && (map->GetPointValue(p.x, p.y - 1) == PointValue::BLANK))
		{
			map->SetPointValue(p.x, p.y - 1, PointValue::FILLED);
			points.emplace_back(p.x, p.y - 1);
		}
		if ((p.y < Map::HEIGHT - 1) && (map->GetPointValue(p.x, p.y + 1) == PointValue::BLANK))
		{
			map->SetPointValue(p.x, p.y + 1, PointValue::FILLED);
			points.emplace_back(p.x, p.y + 1);
		}
	}
}
