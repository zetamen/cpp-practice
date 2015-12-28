#include "stdafx.h"
#include "../Task3_2/Dictionary.cpp"

using namespace std;

struct DictionaryFixture
{
	CDictionary dictionary;
};

BOOST_FIXTURE_TEST_SUITE(Dictionary, DictionaryFixture)

	BOOST_AUTO_TEST_CASE(cant_find_translation_in_empty_dictionary)
	{
		BOOST_CHECK(!dictionary.Find("football"));
	}

	BOOST_AUTO_TEST_CASE(cant_save_if_dont_loading)
	{
		string errorMessage;
		CDictionary tempDictionary;
		BOOST_CHECK(!tempDictionary.Save(errorMessage));
		BOOST_CHECK_EQUAL(errorMessage, "Before save need load file");
	}

	BOOST_AUTO_TEST_CASE(can_create_new)
	{
		string errorMessage;
		BOOST_CHECK(dictionary.Create("db/new_dict.dict", errorMessage));
	}

	BOOST_AUTO_TEST_SUITE(after_add_translation)
		
		BOOST_AUTO_TEST_CASE(can_find_him)
		{
			BOOST_CHECK(dictionary.Add("football", "футбол"));
			auto translation = dictionary.Find("football");
			BOOST_CHECK(translation);
			BOOST_CHECK_EQUAL(translation.value(), "футбол");
		}

		BOOST_AUTO_TEST_CASE(cant_add_translation_twice)
		{
			BOOST_CHECK(dictionary.Add("football", "футбол"));
			BOOST_CHECK(!dictionary.Add("football", "хоккей"));
			auto translation = dictionary.Find("football");
			BOOST_CHECK(translation);
			BOOST_CHECK_EQUAL(translation.value(), "футбол");
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct DictionaryLoadFixture: DictionaryFixture
	{
		string errorMessage;
	};

	BOOST_FIXTURE_TEST_SUITE(when_loading, DictionaryLoadFixture)

		BOOST_AUTO_TEST_CASE(check_if_file_exists)
		{
			BOOST_CHECK(dictionary.LoadFromFile("db/sport.dict", errorMessage));
			BOOST_CHECK(!dictionary.LoadFromFile("db/sport_dont_exists.dict", errorMessage));
		}

		BOOST_AUTO_TEST_CASE(check_if_database_has_empty_lines)
		{
			BOOST_CHECK(!dictionary.LoadFromFile("db/sport_with_empty_lines.dict", errorMessage));
			BOOST_CHECK_EQUAL(errorMessage, "Database damaged: has empty lines");
		}

		BOOST_AUTO_TEST_CASE(check_if_database_has_incorrect_data)
		{
			BOOST_CHECK(!dictionary.LoadFromFile("db/sport_with_incorrect_data.dict", errorMessage));
			BOOST_CHECK_EQUAL(errorMessage, "Database damaged: has incorrect data");
		}

		BOOST_AUTO_TEST_CASE(check_if_database_has_duplicate_keys)
		{
			BOOST_CHECK(!dictionary.LoadFromFile("db/sport_with_duplicate_keys.dict", errorMessage));
			BOOST_CHECK_EQUAL(errorMessage, "Database damaged: has duplicate keys");
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct SportDictionaryFixture : DictionaryLoadFixture
	{
		SportDictionaryFixture()
		{
			dictionary.LoadFromFile("db/sport.dict", errorMessage);
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_database_loaded, SportDictionaryFixture)

		BOOST_AUTO_TEST_CASE(can_find_loaded_translation)
		{
			auto translation = dictionary.Find("football");
			BOOST_CHECK(translation);
			BOOST_CHECK_EQUAL(translation.value(), "футбол");
			translation = dictionary.Find("hockey");
			BOOST_CHECK(translation);
			BOOST_CHECK_EQUAL(translation.value(), "хоккей");
			BOOST_CHECK(!dictionary.Find("tennis"));
		}

		BOOST_AUTO_TEST_CASE(dictionary_cleaning_every_loading)
		{
			BOOST_CHECK(dictionary.LoadFromFile("db/clothes.dict", errorMessage));
			BOOST_CHECK(!dictionary.Find("football"));
		}

		BOOST_AUTO_TEST_CASE(can_save_new_translation_in_file)
		{
			boost::filesystem::remove("db/sport_new.dict");
			dictionary.LoadFromFile("db/sport_new.dict", errorMessage);
			BOOST_CHECK(dictionary.Add("soccer", "классический футбол"));
			BOOST_CHECK(dictionary.Save(errorMessage));
			dictionary.LoadFromFile("db/sport_new.dict", errorMessage);
			auto translation = dictionary.Find("soccer");
			BOOST_CHECK(translation);
			BOOST_CHECK_EQUAL(translation.value(), "классический футбол");
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()