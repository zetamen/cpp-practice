#include "stdafx.h"
#include "../Task3_2/Dictionary.cpp"

struct DictionaryFixture
{
	CDictionary dictionary;
};

BOOST_FIXTURE_TEST_SUITE(Dictionary, DictionaryFixture)

	BOOST_AUTO_TEST_CASE(can_add_translation)
	{
		BOOST_CHECK(dictionary.Add("football", "футбол"));
		BOOST_CHECK(!dictionary.Add("football", "хоккей"));
	}

BOOST_AUTO_TEST_SUITE_END()