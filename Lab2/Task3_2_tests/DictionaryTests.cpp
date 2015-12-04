#include "stdafx.h"
#include "../Task3_2/Dictionary.cpp"

using namespace std;

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
		string errorMessage;
		BOOST_CHECK(dictionary.LoadFromFile("db/sport.dict", errorMessage));
	}

	struct DictionaryLoadingErrorFixture
	{
		string errorMessage;
		CDictionary dictionary;
	};

	BOOST_FIXTURE_TEST_SUITE(when_cant_load_data_from_file, DictionaryLoadingErrorFixture)

		BOOST_AUTO_TEST_CASE(signal_if_file_not_exists)
		{
			BOOST_CHECK(!dictionary.LoadFromFile("db/not_exists_file.dict", errorMessage));
			BOOST_CHECK_EQUAL(errorMessage, "Could not open file");
		}

		BOOST_AUTO_TEST_CASE(signal_if_database_has_empty_lines)
		{
			BOOST_CHECK(!dictionary.LoadFromFile("db/sport_with_empty_lines.dict", errorMessage));
			BOOST_CHECK_EQUAL(errorMessage, "Database damaged: has empty lines");
		}

		BOOST_AUTO_TEST_CASE(signal_if_database_has_incorrect_data)
		{
			BOOST_CHECK(!dictionary.LoadFromFile("db/sport_with_incorrect_data.dict", errorMessage));
			BOOST_CHECK_EQUAL(errorMessage, "Database damaged: has incorrect data");
		}

		BOOST_AUTO_TEST_CASE(signal_if_database_has_duplicate_keys)
		{
			BOOST_CHECK(dictionary.LoadFromFile("db/sport.dict", errorMessage));
			BOOST_CHECK(!dictionary.LoadFromFile("db/sport.dict", errorMessage));
			BOOST_CHECK_EQUAL(errorMessage, "Database damaged: has duplicate keys");
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct SportDictionaryFixture
	{
		SportDictionaryFixture()
		{
			string errorMessage;
			dictionary.LoadFromFile("db/sport.dict", errorMessage);
		}

		CDictionary dictionary;
	};

	BOOST_FIXTURE_TEST_SUITE(when_database_loaded_from_file, SportDictionaryFixture)

		BOOST_AUTO_TEST_CASE(find_translation_from_file)
		{
			auto translation = dictionary.Find("football");
			BOOST_CHECK(translation);
			BOOST_CHECK_EQUAL(translation.value(), "футбол");
			translation = dictionary.Find("hockey");
			BOOST_CHECK(translation);
			BOOST_CHECK_EQUAL(translation.value(), "хоккей");
			BOOST_CHECK(!dictionary.Find("tennis"));
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()