
#include <boost\thread\thread.hpp>
#include "CredentialManager.h"
#include "CredentialManagerTS.h"

#include <opensslv.h>


using namespace boost::unit_test_framework;

namespace CPP_STD_TEST_AND_PRACTIVE_TS {

	void CredentialManagerTS::TestExists() 
	{
		const std::string credName1 = "MyTestCredential";
		const std::string credName2 = "MyTestCredential_None";
		WinAPI::CredentialManager credential1(credName1, WinAPI::CredentialType::Generic);
		WinAPI::CredentialManager credential2(credName2, WinAPI::CredentialType::Generic);

		BOOST_CHECK(credential1.Exists());
		BOOST_CHECK(credential1.Populated());

		BOOST_CHECK(!credential2.Exists());
		BOOST_CHECK(!credential2.Populated());
	}

	void CredentialManagerTS::TestSave() 
	{
		const std::string credName1 = "MyTestCredential2";
		WinAPI::CredentialManager credential1;
		credential1.SetCredName(credName1);
		credential1.SetUserName("testuser");
		credential1.SetSecret("testsecret");
		credential1.SetCredPersistence(WinAPI::CredentialPersistence::Enterprise);
		credential1.SetCredType(1);
		credential1.Save();
	}

	test_suite* CredentialManagerTS::suite() {
		test_suite* suite = BOOST_TEST_SUITE("CredentialManagerTS");
		suite->add(BOOST_TEST_CASE(&TestExists));
		suite->add(BOOST_TEST_CASE(&TestSave));
		return suite;
	}
}