#include "CredentialPrompt.h"

#include "AutoBstr.h"
#include "AutoBuffer.h"
#include "AutoStdString.h"
#include "WinUtils.h"

#include <boost\lexical_cast.hpp>

#include <atlbase.h>

#include <Windows.h>
#include <wincred.h>

namespace KBaseWin 
{
	CredentialPrompt::CredentialPrompt()
		:mDoNotPersist(false), mAlwaysShowUI(false), mGenericCredential(false), mExpectConfirmation(false), mIncorrectPassword(false), mShowSaveCheckBox(false), mKeepUsername(false), mValidateUserName(false)
	{
	}

	bool CredentialPrompt::ShowDialog() 
	{
		USES_CONVERSION;
		CREDUI_INFO info;
		info.cbSize = sizeof(CREDUI_INFO);
		info.hwndParent = NULL;
		info.pszMessageText = A2W(mMessage.c_str());
		info.pszCaptionText = A2W(mTitle.c_str());
		info.hbmBanner = NULL;

		setFlags();

		BOOL saveChecked = mSaveChecked;

		static const size_t MAX_USERNMAE_LENGTH = CREDUI_MAX_USERNAME_LENGTH + 1;
		AutoBuffer<MAX_USERNMAE_LENGTH> username;
		if (!mUsername.empty())
		{
			if (mUsername.size() > MAX_USERNMAE_LENGTH) throw std::runtime_error("The length of user name can't be bigger than " + boost::lexical_cast<std::string>(MAX_USERNMAE_LENGTH));
			std::copy(mUsername.begin(), mUsername.end(), username.mBuffer);
		}
		
		static const size_t MAX_PASSWORD_LENGTH = CREDUI_MAX_PASSWORD_LENGTH + 1;
		AutoBuffer<MAX_PASSWORD_LENGTH> password;
		if (!mSecret.empty()) 
		{
			if (mSecret.size() > MAX_PASSWORD_LENGTH) throw std::runtime_error("The length of password can't be bigger than " + boost::lexical_cast<std::string>(MAX_PASSWORD_LENGTH));
			std::copy(mSecret.begin(), mSecret.end(), password.mBuffer);
		}

		DWORD result = ::CredUIPromptForCredentials(&info,
													A2W(mCredName.c_str()),
													0,
													mErrorCode,
													username.mBuffer,
													MAX_USERNMAE_LENGTH,
													password.mBuffer,
													MAX_PASSWORD_LENGTH,
													&saveChecked,
													mFlags);

		bool dialogResult(false);
		switch(result) 
		{
		case NO_ERROR:
		{
			mUsername = W2A(username.mBuffer);

			mSecret = W2A(password.mBuffer);

			mSaveChecked = 0 != saveChecked;

			dialogResult = true;
			break;
		}
		case ERROR_CANCELLED:
		{
			dialogResult = false;
			break;
		}
		default:
		{
			throw std::runtime_error("Can't get user name and password");
		}
		}

		return dialogResult;
	}

	void CredentialPrompt::setFlags()
	{
		mFlags = 0;
		if (mDoNotPersist) mFlags |= CREDUI_FLAGS_DO_NOT_PERSIST;
		if (mAlwaysShowUI) mFlags |= CREDUI_FLAGS_ALWAYS_SHOW_UI;
		if (mGenericCredential) mFlags |= CREDUI_FLAGS_GENERIC_CREDENTIALS;
		if (mExpectConfirmation) mFlags |= CREDUI_FLAGS_EXPECT_CONFIRMATION;
		if (mIncorrectPassword) mFlags |= CREDUI_FLAGS_INCORRECT_PASSWORD;
		if (mShowSaveCheckBox) mFlags |= CREDUI_FLAGS_SHOW_SAVE_CHECK_BOX;
		if (mKeepUsername) mFlags |= CREDUI_FLAGS_KEEP_USERNAME;
		if (mValidateUserName) mFlags |= CREDUI_FLAGS_VALIDATE_USERNAME;
	}

}