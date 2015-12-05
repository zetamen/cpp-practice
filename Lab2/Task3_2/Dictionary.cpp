#include "stdafx.h"
#include "Dictionary.h"
#include <fstream>
#include <boost\filesystem.hpp>

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
	m_dictionary.clear();
	m_filePath.clear();
	if (!boost::filesystem::exists(filePath))
	{
		m_filePath = filePath;
		return true;
	}
	ifstream file(filePath);
	if (!file.is_open())
	{
		errorMessage = "Could not open file";
		return false;
	}
	m_filePath = filePath;
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
		if (!Add(source, translation))
		{
			errorMessage = "Database damaged: has duplicate keys";
			return false;
		}
	}
	return true;
}

bool CDictionary::Save(string& errorMessage) const
{
	if (m_filePath.empty())
	{
		errorMessage = "Before save need load file";
		return false;
	}
	return true;
}

CDictionary::~CDictionary()
{
}
