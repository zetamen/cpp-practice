#include "stdafx.h"
#include "Dictionary.h"
#include <fstream>

using std::ifstream;


CDictionary::CDictionary()
{
}

bool CDictionary::Add(string const& source, string const& translation)
{
	auto result = m_dictionary.insert(make_pair(source, translation));
	return result.second;
}

boost::optional<string> CDictionary::Find(string const& source) const
{
	auto it = m_dictionary.find(source);
	if (it != m_dictionary.end())
	{
		return it->second;
	}
	return boost::none;
}

bool CDictionary::LoadFromFile(string const& filePath, string& errorMessage)
{
	ifstream file(filePath);
	if (!file.is_open())
	{
		errorMessage = "Could not open file";
		return false;
	}
	string line;
	while (!file.eof())
	{
		getline(file, line);
		if (line.empty())
		{
			if (file.eof())
			{
				return true;
			}
			errorMessage = "Database damaged: has empty lines";
			return false;
		}
		auto separatorIndex = line.find('=');
		if (separatorIndex == string::npos)
		{
			errorMessage = "Database damaged: has incorrect data";
			return false;
		}
		string source = line.substr(0, separatorIndex);
		string translation = line.substr(separatorIndex + 1, line.length() - (separatorIndex + 1));
		Add(source, translation);
	}
	return true;
}

CDictionary::~CDictionary()
{
}
