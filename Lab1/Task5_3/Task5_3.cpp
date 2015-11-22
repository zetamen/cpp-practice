// Task5_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "Map.h"
#include "FileMap.h"
#include "FillAlgorithm.h"

using namespace std;

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
	auto map = FileMap::Read(input);
	if (map == nullptr)
	{
		cout << "Map is incorrect" << endl;
		return 1;
	}
	auto fillAlgorithm = make_shared<FillAlgorithm>();
	map.get()->ApplyAlgorithm(fillAlgorithm);
	FileMap::Write(output, map);
	return 0;
}

