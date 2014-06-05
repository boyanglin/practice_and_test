#ifndef FUNCS_TS_H_
#define FUNCS_TS_H_

#include <boost/test/unit_test.hpp>

namespace CPP_STD_TEST_AND_PRACTIVE_TS
{
	class funcsTS
	{
	public:
		static void sum_square_ts();
		static void simple_thread_example_ts();
		static void multiple_factorial_ts();
		static boost::unit_test_framework::test_suite* suite();
	};
}

#endif 