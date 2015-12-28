#pragma once
#include <string>
#include <map>
#include <boost\optional.hpp>

using std::string;
using std::map;

class CDictionary
{
public:
	CDictionary();
	bool Add(string const& source, string const& translation);
	boost::optional<string> Find(string const& source) const;
	bool LoadFromFile(string const& filePath, string& errorMessage);
	bool Create(string const& filePath, string& errorMessage);
	bool Save(string& errorMessage);
	~CDictionary();
private:
	bool AddToDictionary(string const& source, string const& translation);
	void SaveDictionary(map<string, string> const&  dictionary, std::ofstream& file) const;
private:
	map<string, string> m_dictionary;
	map<string, string> m_newWords;
	string m_filePath;
	bool m_isNew;
};

