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

bool CDictionary::LoadFromFile(string const& filePath)
{
	ifstream file(filePath);
	if (!file.is_open())
	{
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
			return false;
		}
		auto separatorIndex = line.find('=');
		string source = line.substr(0, separatorIndex);
		string translation = line.substr(separatorIndex + 1, line.length() - (separatorIndex + 1));
		Add(source, translation);
	}
	return true;
}

CDictionary::~CDictionary()
{
}
