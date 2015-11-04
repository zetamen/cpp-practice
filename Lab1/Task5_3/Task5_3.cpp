// Task5_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "Map.h"
#include "FillAlgorithm.h"

using namespace std;

shared_ptr<Map> ReadMap(ifstream& input)
{
	vector<string> matrix;
	string row;
	int mapWidth = 0, mapHeight = 0, rowSize;
	while (!input.eof() && (mapHeight < Map::HEIGHT))
	{
		getline(input, row);
		rowSize = row.size();
		if (rowSize > Map::WIDTH)
		{
			row = row.substr(0, Map::WIDTH);
			rowSize = Map::WIDTH;
		}
		if (rowSize > mapWidth)
		{
			mapWidth = rowSize;
		}
		++mapHeight;
		matrix.push_back(row);
	}
	return make_shared<Map>(matrix);
}

void WriteMap(ofstream& output, shared_ptr<Map>& map)
{
	Map* mapPtr = map.get();
	for (int y = 0; y < Map::HEIGHT; ++y)
	{
		for (int x = 0; x < Map::WIDTH; ++x)
		{
			output << mapPtr->GetCharValue(x, y);
		}
		output << endl;
	}
	output << endl;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Format: fill.exe <input file> <output file>" << endl;
		return 1;
	}
	ifstream input(argv[1]);
	if (!input.is_open())
	{
		cout << "File \"" << argv[1] << "\" not open." << endl;
		return 1;
	}
	ofstream output(argv[2]);
	if (!output.is_open())
	{
		cout << "File \"" << argv[2] << "\" not open." << endl;
		return 1;
	}
	auto map = ReadMap(input);
	auto fillAlgorithm = make_shared<FillAlgorithm>();
	map.get()->ApplyAlgorithm(fillAlgorithm);
	WriteMap(output, map);
	return 0;
}

