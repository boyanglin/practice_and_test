#ifndef CREDENTIAL_PROMPT_H_
#define CREDENTIAL_PROMPT_H_

#include <string>
#include "WinUtils.h"

namespace KBaseWin {

	class CredentialPrompt {
	public:

		CredentialPrompt();
		~CredentialPrompt()
		{
			SecureFreeString(&mUsername);
			SecureFreeString(&mSecret);
		}


		std::string mTitle;
		std::string mMessage;
		std::string mCredName;
		bool mDoNotPersist;
		bool mAlwaysShowUI;
		bool mGenericCredential;
		bool mExpectConfirmation;
		bool mIncorrectPassword;
		bool mShowSaveCheckBox;
		bool mKeepUsername;
		bool mValidateUserName;

		bool mSaveChecked;

		bool ShowDialog();

		void SetUsername(const std::string& username) 
		{
			mUsername = username;
		}

		// should pass in encrypted secret
		void SetPassword(const std::string& secret)
		{
			mSecret = secret;
		}

		std::string GetUsername() const
		{
			return mUsername;
		}

		std::string GetSecret() const
		{
			return mSecret;
		}

	private:
		std::string mUsername;
		std::string mSecret;

		unsigned long mFlags;
		void setFlags();

		int mErrorCode;
	};

}

#endif