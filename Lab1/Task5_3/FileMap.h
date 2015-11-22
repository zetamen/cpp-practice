#pragma once
#include "Map.h"

namespace FileMap
{
	shared_ptr<Map> Read(ifstream& input);
	void Write(ofstream& output, shared_ptr<Map> const& map);
	PointValue GetPoint(char const ch);
	char GetChar(PointValue const point);
}
