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
				map->SetPointValue(i, height, GetPoint(row[i]));
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
				output << GetChar(map->GetPointValue(x, y));
			}
			output << endl;
		}
		output << endl;
	}

	PointValue GetPoint(char ch)
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

	char GetChar(PointValue const& point)
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
}
