#include "stdafx.h"
#include "Dictionary.h"
#include <fstream>
#include <boost\filesystem.hpp>


CDictionary::CDictionary()
	:m_isNew(true)
{
}

bool CDictionary::Add(string const& source, string const& translation)
{
	if (Find(source))
	{
		return false;
	}
	m_newWords.insert(make_pair(source, translation));
	return true;
}

boost::optional<string> CDictionary::Find(string const& source) const
{
	auto it = m_dictionary.find(source);
	if (it != m_dictionary.end())
	{
		return it->second;
	}
	it = m_newWords.find(source);
	if (it != m_newWords.end())
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
		m_isNew = true;
		return false;
	}
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		errorMessage = "Could not open file";
		return false;
	}
	m_filePath = filePath;
	m_isNew = false;
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
		if (!AddToDictionary(source, translation))
		{
			errorMessage = "Database damaged: has duplicate keys";
			return false;
		}
	}
	return true;
}

bool CDictionary::Create(string const& filePath, string& errorMessage)
{
	return true;
}

bool CDictionary::Save(string& errorMessage)
{
	if (m_filePath.empty())
	{
		errorMessage = "Before save need load file";
		return false;
	}
	if (m_dictionary.empty() && m_newWords.empty())
	{
		errorMessage = "Dictionary is empty";
		return false;
	}
	std::ofstream file;
	file.open(m_filePath, m_isNew ? std::ios_base::out : std::ios_base::out | std::ios_base::app);
	if (!file.is_open())
	{
		errorMessage = "Could not open file";
		return false;
	}
	if (m_isNew)
	{
		SaveDictionary(m_dictionary, file);
	}
	SaveDictionary(m_newWords, file);
	m_dictionary.insert(m_newWords.begin(), m_newWords.end());
	m_newWords.clear();
	return true;
}

bool CDictionary::AddToDictionary(string const& source, string const& translation)
{
	auto result = m_dictionary.insert(make_pair(source, translation));
	return result.second;
}

void CDictionary::SaveDictionary(map<string, string> const&  dictionary, std::ofstream& file) const
{
	std::transform(
		dictionary.begin(),
		dictionary.end(),
		std::ostream_iterator<string>(file),
		[](const std::pair<string, string>& data)
		{
			return data.first + '=' + data.second + '\n';
		}
	);
}

CDictionary::~CDictionary()
{
}