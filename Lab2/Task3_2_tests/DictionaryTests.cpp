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

	BOOST_AUTO_TEST_CASE(can_find_translation)
	{
		BOOST_CHECK(!dictionary.Find("football"));
		dictionary.Add("football", "футбол");
		auto translation = dictionary.Find("football");
		BOOST_CHECK(translation);
		BOOST_CHECK_EQUAL(translation.value(), "футбол");
	}

	BOOST_AUTO_TEST_CASE(can_load_translations_from_file)
	{
		BOOST_CHECK(!dictionary.LoadFromFile("db/not_exists_file.dict"));
		BOOST_CHECK(dictionary.LoadFromFile("db/sport.dict"));
	}

BOOST_AUTO_TEST_SUITE_END()