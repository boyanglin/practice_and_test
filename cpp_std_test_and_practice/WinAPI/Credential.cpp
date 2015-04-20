#include "Credential.h"

#include "AutoBstr.h"
#include "AutoCredentialBuffer.h"
#include "CredentialConsts.h"

#include "WinUtils.h"

#include <boost\lexical_cast.hpp>

#include <atlbase.h>
#include <wincred.h>
#include <Windows.h>

#include <memory>

namespace KBaseWin {


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Credential::Credential() : mCredType(0), mPersistence(0), mPopulated(false) 
	{
	}

	Credential::Credential(const std::string& credName, unsigned long credType) 
		: mCredType(0), mPersistence(0), mPopulated(false) 
	{
		// yapfbj: todo change to KBase assert
		if (credName.empty()) throw std::runtime_error("Invalid credential name");
		Load(credName, credType);
	}

	Credential::~Credential() {}

	bool Credential::isContentValid() const
	{
		return (!mCredName.empty() && !mUsername.empty() && !mSecret.empty() && mPersistence > CredentialPersistence::PersistenceNone && CredentialType::IsValid(mCredType));
	}

	bool Credential::Load(const std::string& credName, unsigned long credType)
	{
		AutoCredentialBuffer aAutoCredentialBuffer;
		mPopulated = false;
		if (0 != ::CredRead(std::wstring(credName.begin(), credName.end()).c_str(), static_cast<DWORD>(credType), 0, &aAutoCredentialBuffer.mPCREDENTIAL))
		{
			mCredName = CW2A(aAutoCredentialBuffer.mPCREDENTIAL->TargetName);
			mUsername = CW2A(aAutoCredentialBuffer.mPCREDENTIAL->UserName);
			mPersistence = aAutoCredentialBuffer.mPCREDENTIAL->Persist;
			mCredType = aAutoCredentialBuffer.mPCREDENTIAL->Type;
			// ***************************************************************************************
			//TODO: this part should be revised. convert std::string to LPBYTE is not ideal here
			//TODO: we have to encrypt secret here
			mSecret = CW2A(reinterpret_cast<LPCWSTR>(aAutoCredentialBuffer.mPCREDENTIAL->CredentialBlob));
			// ***************************************************************************************

			mPopulated = true;
			return true;
		}
		else
		{
			return false;
		}
	}

	void Credential::SetCredName(const std::string& credName)
	{
		if (credName.empty()) throw std::runtime_error("Credential name can't be empty.");
		mCredName = credName;
	}

	void Credential::SetUserName(const std::string& userName)
	{
		if (userName.empty()) throw std::runtime_error("User name can't be empty.");
		mUsername = userName;
	}

	void Credential::SetSecret(const std::string& secret)
	{
		//TODO: we have to encrypt the secret here
		if (secret.empty()) throw std::runtime_error("User name can't be empty.");
		mSecret = secret;
	}
	
	void Credential::SetCredPersistence(unsigned long persistence)
	{
		if (persistence == 0) throw std::runtime_error("Credential persistence can't be 0.");
		mPersistence = persistence;
	}

	void Credential::SetCredType(unsigned long credType)
	{
		if (credType == 0) throw std::runtime_error("Credential type can't be 0.");
		mCredType = credType;
	}

	void Credential::Save() const
	{
		if (!isContentValid())
			throw std::runtime_error("Can't save an empty credential.");

		USES_CONVERSION;
		CREDENTIAL aCredential = { 0 };
		aCredential.Type = mCredType;
		aCredential.TargetName = A2W(mCredName.c_str());
		aCredential.UserName = A2W(mUsername.c_str());
		aCredential.Persist = mPersistence;

		// ***************************************************************************************
		//TODO: this part should be revised. convert std::string to LPBYTE is not ideal here
		//TODO: we have to decrypt secret here

		//method 1
		//int aSecretLength = 0;
		//AutoPasswordBstr aAutoSecretBstr;
		//aAutoSecretBstr.Set(toBSTR(aSecretLength, mSecret));
		//aCredential.CredentialBlob = reinterpret_cast<LPBYTE>(aAutoSecretBstr.Get());

		//method 2
		std::wstring aTemp(mSecret.begin(), mSecret.end());
		AutoWStr autoWstr;
		autoWstr.Set(&aTemp);
		aCredential.CredentialBlob = reinterpret_cast<LPBYTE>(const_cast<wchar_t*>(autoWstr.Get()->c_str()));

		//method3
		//aCredential.CredentialBlob = reinterpret_cast<LPBYTE>(const_cast<char*>(mSecret.c_str()));
		// ***************************************************************************************
		
		aCredential.CredentialBlobSize = aTemp.length() * sizeof (wchar_t);

		AutoCredentialBuffer aAutoCredentialBuffer;
		aAutoCredentialBuffer.mPCREDENTIAL = &aCredential;

		if(!CredWriteW(&aCredential, 0))
		{
			DWORD aResult = ::GetLastError();
			switch (aResult)
			{
			case ERROR_NO_SUCH_LOGON_SESSION:
			{
				throw std::runtime_error(std::string(__FUNCTION__) + " Can't find credential");
			}
			case ERROR_BAD_USERNAME:
			{
				throw std::runtime_error(std::string(__FUNCTION__) + " Invalid user name");
			}
			default:
			{
				throw std::runtime_error(std::string(__FUNCTION__) + " Unknown error.");
			}
			}
		}
	}

	bool Credential::Delete(const std::string& credName, unsigned long credType) 
	{
		if (credName.empty()) std::runtime_error("Credential name can't be empty.");
		if (!CredentialType::IsValid(credType)) std::runtime_error("Invalid credential type: " + boost::lexical_cast<std::string>(credType));
		
		USES_CONVERSION;
		if (!CredDelete(A2W(credName.c_str()), static_cast<DWORD>(credType), 0/*reserved*/)) 
		{
			DWORD aResult = ::GetLastError();

			switch (aResult)
			{
			case ERROR_NOT_FOUND:
			{
				throw std::runtime_error("Can't find this credential");
			}
			case ERROR_NO_SUCH_LOGON_SESSION:
			{
				throw std::runtime_error("Can't find this login session");
			}
			default:
			{
				throw std::runtime_error("Unknown error");
			}
			}
		}

		return true;
	}
	
	//void Credential::getCredContent(const AutoCredentialBuffer& autoCredentialBuffer)
	//{
	//	mCredName = CW2A(autoCredentialBuffer.mPCREDENTIAL->TargetName);
	//	mUsername = CW2A(autoCredentialBuffer.mPCREDENTIAL->UserName);
	//	mPersistence = autoCredentialBuffer.mPCREDENTIAL->Persist;
	//	mCredType = autoCredentialBuffer.mPCREDENTIAL->Type;
	//	mSecret = CW2A(reinterpret_cast<LPCWSTR>(autoCredentialBuffer.mPCREDENTIAL->CredentialBlob));

	//	////second method to covert lpbyte to string
	//	//int size_needed = WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<LPCWSTR>(autoCredentialBuffer.mPCREDENTIAL->CredentialBlob), autoCredentialBuffer.mPCREDENTIAL->CredentialBlobSize / 2, NULL, 0, NULL, NULL);
	//	//std::unique_ptr<char> secret(new char[size_needed]);
	//	//WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<LPCWSTR>(autoCredentialBuffer.mPCREDENTIAL->CredentialBlob), autoCredentialBuffer.mPCREDENTIAL->CredentialBlobSize / 2, secret.get(), size_needed, NULL, NULL);
	//	//mSecret = std::string(secret.get(), secret.get() + size_needed);
	//}
}