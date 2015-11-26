#include "boost_qi.h"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_numeric.hpp>

#include <string>
#include <iostream>

#include <regex>

using namespace boost::unit_test_framework;

#define TEST_MACRO_1(n, str) std::string var##n = str;\
	std::cout << "\"" << str << "\"" << " is double : " << (isDouble(var##n)? "true":"false") << std::endl;\
	std::cout << "\"" << str << "\"" << " is number2: " << (isNumber2(var##n) ? "true" : "false") << std::endl
	//std::cout << "\"" << str << "\"" << " is long   : " << (isLong(var##n)? "true":"false") << std::endl;
	//std::cout << "\"" << str << "\"" << " is number : " << (isNumber(var##n)? "true":"false") << std::endl;

namespace
{
	bool isDouble(std::string str)
	{
		std::string::const_iterator first(str.begin()), last(str.end());
		return boost::spirit::qi::phrase_parse(first, last, boost::spirit::double_, boost::spirit::ascii::space) && first == last;
	}
	bool isLong(std::string str)
	{
		std::string::const_iterator first(str.begin()), last(str.end());
		return boost::spirit::qi::phrase_parse(first, last, boost::spirit::long_, boost::spirit::ascii::space) && first == last;
	}

	bool isNumber(std::string str)
	{
		std::string::const_iterator first(str.begin()), last(str.end());
		return boost::spirit::qi::phrase_parse(first, last, boost::spirit::long_ || boost::spirit::double_, boost::spirit::ascii::space) && first == last;

	}

	bool isNumber2(std::string str)
	{

		return std::regex_match(str, std::regex("\\s*(\\+|-)?[0-9]*(\\.(([0-9]*)?))?((e|E)((\\+|-)?)[0-9]+)?\\s*"));
	}
}

namespace Boost_Example
{
	void testFunc1()
	{
		TEST_MACRO_1(1, "123");
		TEST_MACRO_1(2, "123.456"); 
		TEST_MACRO_1(3, ".456"); 
		TEST_MACRO_1(4, "123."); 
		TEST_MACRO_1(5, "+123.");
		TEST_MACRO_1(6, "-123");
		TEST_MACRO_1(7, "   123.456   "); 
		TEST_MACRO_1(8, "123.456 "); 
		TEST_MACRO_1(9, "   123.456"); 
		TEST_MACRO_1(10, " 123.456 789 "); 
		TEST_MACRO_1(11, " 1e5 "); 
		TEST_MACRO_1(12, " 1.2e5 "); 
		TEST_MACRO_1(13, " 1.2e-5 "); 
		TEST_MACRO_1(14, " +1.2e-5 ");
		TEST_MACRO_1(15, " adb fdgdf ");
		TEST_MACRO_1(16, " . ");




	}
}


namespace CPP_STD_TEST_AND_PRACTIVE_TS
{
	test_suite* BOOST_QI_TS::suite()
	{
		test_suite* suite = BOOST_TEST_SUITE("BOOST_QI_TS");
		suite->add(BOOST_TEST_CASE(&Boost_Example::testFunc1));
		return suite;
	}
}
