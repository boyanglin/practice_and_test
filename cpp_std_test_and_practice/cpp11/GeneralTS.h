#ifndef GENERAL_TS_H_
#define GENERAL_TS_H_

#include <boost/test/unit_test.hpp>

namespace CPP_STD_TEST_AND_PRACTIVE_TS {

	class GeneralTS {
	public:
		static void TestFuncs();
		static void TestSharedPtrOfArray();
		static void TestDeleter();
		static void TestNumberLimit();
		static  boost::unit_test_framework::test_suite* suite();
	};
} //namespace CPP_STD_TEST_AND_PRACTIVE_TS

#endif //R_VALUE_TS_H_