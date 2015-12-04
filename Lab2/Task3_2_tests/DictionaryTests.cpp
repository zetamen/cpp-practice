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

	struct DictionaryLoadFixture : DictionaryFixture
	{
		string errorMessage;
	};

	BOOST_FIXTURE_TEST_SUITE(can_load_translations_from_file, DictionaryLoadFixture)

		BOOST_AUTO_TEST_CASE(if_file_exists)
		{
			BOOST_CHECK(dictionary.LoadFromFile("db/sport.dict", errorMessage));
		}

		BOOST_AUTO_TEST_CASE(save_path_if_file_not_exists)
		{
			string errorMessage;
			BOOST_CHECK(dictionary.LoadFromFile("db/sport_new.dict", errorMessage));
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
			BOOST_CHECK(!dictionary.LoadFromFile("db/sport_with_duplicate_keys.dict", errorMessage));
			BOOST_CHECK_EQUAL(errorMessage, "Database damaged: has duplicate keys");
		}

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

		BOOST_AUTO_TEST_CASE(when_load_again_old_data_is_clear)
		{
			string errorMessage;
			BOOST_CHECK(dictionary.LoadFromFile("db/clothes.dict", errorMessage));
			BOOST_CHECK(!dictionary.Find("football"));
		}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()