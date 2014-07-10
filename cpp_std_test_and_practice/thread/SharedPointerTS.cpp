#include <memory>
#include <string>
#include "SharedPointer.h"

#include "SharedPointerTS.h"

using namespace boost::unit_test_framework;

namespace CPP_STD_TEST_AND_PRACTIVE_TS
{

void SharedPointerTS::TestFuncs() {
	std::string* szTest = new std::string("CPP_STD_TEST_AND_PRACTIVE_TS");
	std::shared_ptr<std::string> pTest1(szTest);
	std::shared_ptr<std::string> pTest2 = pTest1;
	BOOST_CHECK(SharedPointer::ifTwoSharedPtrTheSame(pTest1, pTest2));
}

test_suite* SharedPointerTS::suite()
{
	test_suite* suite = BOOST_TEST_SUITE("SharedPointerTS");
	//suite->add(BOOST_TEST_CASE(&first_test));
	suite->add(BOOST_TEST_CASE(&TestFuncs));
	return suite;
}
}