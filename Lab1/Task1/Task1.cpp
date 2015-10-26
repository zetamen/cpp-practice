// Task1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

const int BUFFER_LENGTH = 100;

void FileCopy(ifstream& input, ofstream& output)
{
	char buffer[BUFFER_LENGTH];
	while (!input.eof())
	{
		input.get(buffer, BUFFER_LENGTH, '\0');
		output.write(buffer, input.gcount());
	}
	output.close();
}

vector<int> GetPrefix(string str)
{
	int size = str.length();
	vector<int> prefix(size);
	prefix[0] = 0;
	for (int i = 1; i < size; ++i)
	{
		int k = prefix[i - 1];
		while ((k > 0) && (str[i] != str[k]))
		{
			k = prefix[k - 1];
		}
		if (str[i] == str[k])
		{
			++k;
		}
		prefix[i] = k;
	}
	return prefix;
}

void ReplaceText(ifstream& input, ofstream& output, const string& search, const string& replace)
{
	string store;
	char buffer[BUFFER_LENGTH];
	vector<int> prefix = GetPrefix(search);
	int searchSize = search.size(), k = 0;
	bool isShifting;
	while (!input.eof())
	{
		input.get(buffer, BUFFER_LENGTH, '\0');
		auto bufferSize = input.gcount();
		for (int i = 0; i < bufferSize; ++i)
		{
			isShifting = false;
			while ((k > 0) && (search[k] != buffer[i]))
			{
				k = prefix[k - 1];
				isShifting = true;
			}
			if (isShifting)
			{
				if (k > 0)
				{
					store.erase(store.size() - k, k);
				}
				output << store;
				store.clear();
			}
			if (search[k] == buffer[i])
			{
				store.push_back(buffer[i]);
				++k;
			}
			else
			{
				output << buffer[i];
			}
			if (k == searchSize)
			{
				store.clear();
				output << replace;
				k = 0;
			}
		}
	}
	if (!store.empty())
	{
		output << store;
		store.clear();
	}
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Format: replace.exe <input file> <output file> <search string> <replace string>" << endl;
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
	;
	string search = argv[3], replace = argv[4];
	if (search.length() == 0)
	{
		FileCopy(input, output);
		return 0;
	}
	ReplaceText(input, output, search, replace);
	return 0;
}
