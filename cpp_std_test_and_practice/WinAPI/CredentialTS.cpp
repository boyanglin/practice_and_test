#include "CredentialTS.h"

#include <boost\thread\thread.hpp>

#include "ChangeCredential.h"
#include "Credential.h"
#include "CredentialConsts.h"
#include "CredentialPrompt.h"

using namespace boost::unit_test_framework;

namespace CPP_STD_TEST_AND_PRACTIVE_TS
{

    void CredentialTS::TestExists()
    {
        const std::string credName1 = "MyTestCredential";
        const std::string credName2 = "MyTestCredential_None";
        KBaseWin::Credential credential1(credName1, KBaseWin::CredentialType::Generic);
        KBaseWin::Credential credential2(credName2, KBaseWin::CredentialType::Generic);

        BOOST_CHECK(credential1.Exists());
        BOOST_CHECK(credential1.Populated());

        BOOST_CHECK(!credential2.Exists());
        BOOST_CHECK(!credential2.Populated());
    }

    void CredentialTS::TestSave()
    {
        const std::string CRED_NAME = "MyTestCredential2";
        const std::string USER_NAME = "testuser";
        const std::string SECRET = "testsecret";

        KBaseWin::Credential credential1;
        credential1.SetCredName(CRED_NAME);
        credential1.SetUserName(USER_NAME);
        credential1.SetSecret(SECRET);
        credential1.SetCredPersistence(KBaseWin::CredentialPersistence::Enterprise);
        credential1.SetCredType(KBaseWin::CredentialType::Generic);
        credential1.Save();

        KBaseWin::Credential credential2(CRED_NAME, KBaseWin::CredentialType::Generic);
        BOOST_CHECK(credential2.Populated());
        BOOST_CHECK(credential2.Exists());
        BOOST_CHECK(credential2.GetCredName() == CRED_NAME);
        BOOST_CHECK(credential2.GetUsername() == USER_NAME);
        BOOST_CHECK(credential2.GetSecret() == SECRET);
        BOOST_CHECK(credential2.GetCredType() == KBaseWin::CredentialType::Generic);
        BOOST_CHECK(credential2.GetCredPersistence() == KBaseWin::CredentialPersistence::Enterprise);

        BOOST_CHECK(KBaseWin::Credential::Delete(CRED_NAME, KBaseWin::CredentialType::Generic));

    }

    void CredentialTS::TestPrompt()
    {
        KBaseWin::CredentialPrompt prompt1;
        prompt1.mTitle = "This is a test.";
        prompt1.mMessage = "Please input your credential";
        prompt1.mCredName = "TestCredential";
        prompt1.mSaveChecked = true;
        prompt1.mGenericCredential = true;
        prompt1.mExpectConfirmation = true;
        prompt1.mAlwaysShowUI = true;
        BOOST_CHECK(prompt1.ShowDialog());
        std::string username = prompt1.GetUsername();
        std::string password = prompt1.GetSecret();
    }

    void CredentialTS::TestChangePassword()
    {
        KBaseWin::ChangeCredential aChangeCredential("Discovery");
        aChangeCredential.PopupWindow();
    }

    test_suite* CredentialTS::suite()
    {
        test_suite* suite = BOOST_TEST_SUITE("CredentialTS");
        suite->add(BOOST_TEST_CASE(&TestExists));
        suite->add(BOOST_TEST_CASE(&TestSave));
        suite->add(BOOST_TEST_CASE(&TestPrompt));
        suite->add(BOOST_TEST_CASE(&TestChangePassword));
        return suite;
    }
}