#include <iostream>

#include "GeneralTS.h"
#include "RValueTS.h"
#include "PolymorphismTS.h"
#include "Iterator.h"
#include "Boost_FileSystem.h"
#include "boost_qi.h"

#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

// Test suite initializer hook called by boost:unit_test
test_suite* init_unit_test_suite(int, char*[])
{
	std::string header = "cpp11 UnitTests";
	std::string rule = std::string(header.length(), '=');
	BOOST_MESSAGE(rule);
	BOOST_MESSAGE(header);
	BOOST_MESSAGE(rule);

	boost::unit_test::unit_test_log.set_threshold_level(boost::unit_test::log_test_units);

	// Add all test suites
	framework::master_test_suite().add(CPP_STD_TEST_AND_PRACTIVE_TS::RValueTS::suite());
	framework::master_test_suite().add(CPP_STD_TEST_AND_PRACTIVE_TS::GeneralTS::suite());
	framework::master_test_suite().add(CPP_STD_TEST_AND_PRACTIVE_TS::PolymorphismTS::suite());
	framework::master_test_suite().add(CPP_STD_TEST_AND_PRACTIVE_TS::IteratorTS::suite());
	framework::master_test_suite().add(CPP_STD_TEST_AND_PRACTIVE_TS::Boost_FileSystemTS::suite());
	framework::master_test_suite().add(CPP_STD_TEST_AND_PRACTIVE_TS::BOOST_QI_TS::suite());

	return 0;
}