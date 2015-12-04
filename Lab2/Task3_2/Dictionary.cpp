#include "stdafx.h"
#include "Dictionary.h"
#include <fstream>


CDictionary::CDictionary()
{
}

bool CDictionary::Add(string const & source, string const & translation)
{
	auto result = m_dictionary.insert(make_pair(source, translation));
	return result.second;
}

boost::optional<string> CDictionary::Find(string const & source) const
{
	auto it = m_dictionary.find(source);
	if (it != m_dictionary.end())
	{
		return it->second;
	}
	return boost::none;
}

CDictionary::~CDictionary()
{
}
