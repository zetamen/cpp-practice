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

CDictionary::~CDictionary()
{
}
