#pragma once
#include "Map.h"

namespace FileMap
{
	unique_ptr<Map> Read(ifstream& input);
	void Write(ofstream& output, Map const* map);
	PointType GetPoint(char ch);
	char GetChar(PointType const& point);
}
