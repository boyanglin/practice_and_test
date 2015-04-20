#include <iostream>

#include <boost/test/unit_test.hpp>

#include "CryptoppTS.h"

using namespace boost::unit_test;

// Test suite initializer hook called by boost:unit_test
test_suite* init_unit_test_suite(int, char*[])
{
	std::string header = "3rdParty UnitTests";
	std::string rule = std::string(header.length(), '=');
	BOOST_MESSAGE(rule);
	BOOST_MESSAGE(header);
	BOOST_MESSAGE(rule);

	framework::master_test_suite().add(CPP_STD_TEST_AND_PRACTIVE_TS::CryptoppTS::suite());

	return 0;
}