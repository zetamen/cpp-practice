#pragma once
#include <string>
#include <map>

using namespace std;

class CDictionary
{
public:
	CDictionary();
	bool Add(string const& source, string const& translation);

	~CDictionary();
private:
	map<string, string> m_dictionary;
};

