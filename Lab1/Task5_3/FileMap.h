#pragma once
#include "Map.h"

class FileMap
{
public:
	FileMap();
	shared_ptr<Map> Read(ifstream& input);
	void Write(ofstream& output, shared_ptr<Map> const& map);
	PointValue GetPoint(char const ch) const;
	char GetChar(PointValue const point) const;
	~FileMap();
};

