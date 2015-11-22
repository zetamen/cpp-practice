#include "stdafx.h"
#include "FileMap.h"
#include <fstream>
#include <string>

namespace FileMap
{
	unique_ptr<Map> Read(ifstream& input)
	{
		vector<string> matrix;
		string row;
		if (input.eof())
		{
			return nullptr;
		}
		auto map = make_unique<Map>();
		int height = 0, rowSize = 0, i;
		while (!input.eof() && (height < Map::HEIGHT))
		{
			getline(input, row);
			rowSize = (row.size() > Map::WIDTH) ? Map::WIDTH : row.size();
			for (i = 0; i < rowSize; ++i)
			{
				map->SetPointType(i, height, GetPoint(row[i]));
			}
			++height;
		}
		return map;
	}

	void Write(ofstream & output, Map const* map)
	{
		for (int y = 0; y < Map::HEIGHT; ++y)
		{
			for (int x = 0; x < Map::WIDTH; ++x)
			{
				output << GetChar(map->GetPointType(x, y));
			}
			output << endl;
		}
		output << endl;
	}

	PointType GetPoint(char ch)
	{
		PointType point;
		switch (ch)
		{
		case '#':
			point = PointType::BLOCK;
			break;
		case 'O':
			point = PointType::START;
			break;
		case '.':
			point = PointType::FILLED;
			break;
		default:
			point = PointType::BLANK;
			break;
		}
		return point;
	}

	char GetChar(PointType const& point)
	{
		char ch;
		switch (point)
		{
		case PointType::BLOCK:
			ch = '#';
			break;
		case PointType::START:
			ch = 'O';
			break;
		case PointType::FILLED:
			ch = '.';
			break;
		default:
			ch = ' ';
			break;
		}
		return ch;
	}
}
