#ifndef CREDENTIAL_MANAGER_TS_H_
#define CREDENTIAL_MANAGER_TS_H_

#include <boost/test/unit_test.hpp>

namespace CPP_STD_TEST_AND_PRACTIVE_TS
{

	class CredentialTS
	{
	public:
		static void TestExists();
		static void TestSave();
		static void TestPrompt();
		static void TestChangePassword();
		static  boost::unit_test_framework::test_suite* suite();
	};


} //namespace CPP_STD_TEST_AND_PRACTIVE_TS


#endif