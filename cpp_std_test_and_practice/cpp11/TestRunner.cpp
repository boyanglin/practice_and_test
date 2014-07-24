#include <iostream>

#include "GeneralTS.h"
#include "RValueTS.h"

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

	// Add all test suites
	//framework::master_test_suite().add(CPP_STD_TEST_AND_PRACTIVE_TS::RValueTS::suite());
	framework::master_test_suite().add(CPP_STD_TEST_AND_PRACTIVE_TS::GeneralTS::suite());

	return 0;
}