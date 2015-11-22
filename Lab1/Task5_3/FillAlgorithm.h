#pragma once
#include <vector>
#include "Map.h"
#include "Point.h"

using namespace std;

class FillAlgorithm
{
public:
	static void Apply(Map* map);
private:
	static vector<Point> GetStartPoints(Map const* map);
	static void Fill(Point point, Map* const map);
};

