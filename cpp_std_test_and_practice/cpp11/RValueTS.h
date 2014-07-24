#ifndef R_VALUE_TS_H_
#define R_VALUE_TS_H_

#include <boost/test/unit_test.hpp>

namespace CPP_STD_TEST_AND_PRACTIVE_TS {

	class RValueTS {
	public:
		static void TestFuncs();
		static void TestClass1();
		static  boost::unit_test_framework::test_suite* suite();
	};
} //namespace CPP_STD_TEST_AND_PRACTIVE_TS

#endif //R_VALUE_TS_H_