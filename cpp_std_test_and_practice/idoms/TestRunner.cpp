#include "AttorneyClientTS.h"

#include <boost/test/unit_test.hpp>

#include <iostream>

using namespace boost::unit_test;

// Test suite initializer hook called by boost:unit_test
test_suite* init_unit_test_suite(int, char*[])
{
    std::string header = "Idioms UnitTests";
    std::string rule = std::string(header.length(), '=');
    BOOST_MESSAGE(rule);
    BOOST_MESSAGE(header);
    BOOST_MESSAGE(rule);

	framework::master_test_suite().add(Idioms_TS::AttorneyClientTS::suite());

    return 0;
}