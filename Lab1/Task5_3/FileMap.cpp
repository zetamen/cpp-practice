#include "stdafx.h"
#include "FileMap.h"
#include <fstream>
#include <string>

namespace FileMap
{
	shared_ptr<Map> Read(ifstream& input)
	{
		vector<string> matrix;
		string row;
		if (input.eof())
		{
			return nullptr;
		}
		auto map = make_shared<Map>();
		auto mapPtr = map.get();
		int height = 0, rowSize = 0, i;
		while (!input.eof() && (height < Map::HEIGHT))
		{
			getline(input, row);
			rowSize = (row.size() > Map::WIDTH) ? Map::WIDTH : row.size();
			for (i = 0; i < rowSize; ++i)
			{
				mapPtr->SetPointValue(i, height, GetPoint(row[i]));
			}
			++height;
		}
		return map;
	}

	void Write(ofstream & output, shared_ptr<Map> const& map)
	{
		Map* mapPtr = map.get();
		for (int y = 0; y < Map::HEIGHT; ++y)
		{
			for (int x = 0; x < Map::WIDTH; ++x)
			{
				output << GetChar(mapPtr->GetPointValue(x, y));
			}
			output << endl;
		}
		output << endl;
	}

	PointValue GetPoint(char const ch)
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

	char GetChar(PointValue const point)
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
