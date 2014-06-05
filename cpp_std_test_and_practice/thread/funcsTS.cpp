
#include "funcs.h"
#include "funcsTS.h"

using namespace boost::unit_test_framework;

namespace CPP_STD_TEST_AND_PRACTIVE_TS {

	void funcsTS::multiple_factorial_ts() {
		TestFuncs::sum_square(100);
		BOOST_CHECK(true);
	}

	void funcsTS::simple_thread_example_ts() {
		TestFuncs::multiple_factorial(100, 200);
		BOOST_CHECK(true);
	}

	void funcsTS::sum_square_ts() {
		TestFuncs::simple_thread_example();
		BOOST_CHECK(true);
	}

	test_suite* funcsTS::suite()
	{
		test_suite* suite = BOOST_TEST_SUITE("funcsTS");

		suite->add(BOOST_TEST_CASE(&multiple_factorial_ts));
		suite->add(BOOST_TEST_CASE(&simple_thread_example_ts));
		suite->add(BOOST_TEST_CASE(&sum_square_ts));

		return suite;
	}
}