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
	~CDictionary();
private:
	map<string, string> m_dictionary;
};

