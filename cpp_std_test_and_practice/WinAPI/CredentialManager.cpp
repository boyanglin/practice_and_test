#include "CredentialManager.h"

#include "AutoCredentialBuffer.h"
//#include "WinUtils.h"
#include <atlbase.h>
//#include <atlconv.h>

#include <Windows.h>
#include <wincred.h>

#include <memory>

namespace WinAPI {
//////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	const unsigned long CredentialType::TypeNone = 0;
	const unsigned long CredentialType::Generic = CRED_TYPE_GENERIC;
	const unsigned long CredentialType::DomainPassword = CRED_TYPE_DOMAIN_PASSWORD;
	const unsigned long CredentialType::DomainCertificate = CRED_TYPE_DOMAIN_CERTIFICATE;
	const unsigned long CredentialType::DomainVisiblePassword = CRED_TYPE_DOMAIN_VISIBLE_PASSWORD;

	const unsigned long CredentialPersistence::PersistenceNone = 0;
	const unsigned long CredentialPersistence::Session = CRED_PERSIST_SESSION;
	const unsigned long CredentialPersistence::LocalComputer = CRED_PERSIST_LOCAL_MACHINE;
	const unsigned long CredentialPersistence::Enterprise = CRED_PERSIST_ENTERPRISE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class CredentialManager::CredentialManageImp
	{
	public:
		CredentialManageImp();
		CredentialManageImp(const std::string& credName, unsigned long credType);

		bool Load(const std::string& credName, unsigned long credType);
		bool Populated() { return mPopulated; }
		bool Exists() { return mPopulated; }

		void SetCredName(const std::string& credName);
		void SetUserName(const std::string& userName);
		void SetSecret(const std::string& secret);
		void SetCredPersistence(unsigned long persistence);
		void SetCredType(unsigned long credType);

		std::string GetCredname() const { return mCredName; }
		std::string GetSecret() const { return mSecret; }
		std::string GetUsername() const { return mUserName; }
		unsigned long GetCredPersistence() const { return mPersistence; }
		unsigned long GetCredType() const { return mCredType; }

		void Save() const;

	private:

		std::string mCredName;
		std::string mUserName;
		std::string mSecret;
		unsigned long mCredType;
		unsigned long mPersistence;

		bool mPopulated;

		bool exists(const std::string& credName, unsigned long credType);
		void getCredContent(const AutoCredentialBuffer& autoCredentialBuffer);

		bool isContentValid() const;
	};

	CredentialManager::CredentialManageImp::CredentialManageImp()
		: mCredType(0), mPersistence(0), mPopulated(false)
	{
	}

	CredentialManager::CredentialManageImp::CredentialManageImp(const std::string& credName, unsigned long credType)
		: mCredType(0), mPersistence(0), mPopulated(false)
	{
		// yapfbj: todo change to KBase assert
		if (credName.empty()) throw std::runtime_error("Invalid credential name");
		Load(credName, credType);
	}

	bool CredentialManager::CredentialManageImp::isContentValid() const
	{
		return (!mCredName.empty() && !mUserName.empty() && !mSecret.empty() && mPersistence > CredentialPersistence::PersistenceNone && mCredType > CredentialType::TypeNone);
	}

	void CredentialManager::CredentialManageImp::SetCredName(const std::string& credName)
	{
		if (credName.empty()) throw std::runtime_error("Credential name can't be empty.");
		mCredName = credName;
	}

	void CredentialManager::CredentialManageImp::SetUserName(const std::string& userName) 
	{
		if (userName.empty()) throw std::runtime_error("User name can't be empty.");
		mUserName = userName;
	}

	void CredentialManager::CredentialManageImp::SetSecret(const std::string& secret)
	{
		if (secret.empty()) throw std::runtime_error("User name can't be empty.");
		mSecret = secret;
	}

	void CredentialManager::CredentialManageImp::SetCredPersistence(unsigned long persistence)
	{
		if (persistence == 0) throw std::runtime_error("Credential persistence can't be 0.");
		mPersistence = persistence;
	}

	void CredentialManager::CredentialManageImp::SetCredType(unsigned long credType)
	{
		if (credType == 0) throw std::runtime_error("Credential type can't be 0.");
		mCredType = credType;
	}

	void CredentialManager::CredentialManageImp::Save() const
	{
		if (!isContentValid()) 
			throw std::runtime_error("Can't save an empty credential.");

		USES_CONVERSION;
		CREDENTIAL credential = { 0 };
		credential.Type = mCredType;
		credential.TargetName = A2W(mCredName.c_str());
		credential.UserName = A2W(mUserName.c_str());
		credential.Persist = mPersistence;
		char *test = const_cast<char*>(mSecret.c_str());
		credential.CredentialBlob = (LPBYTE)test;
		credential.CredentialBlobSize = mSecret.size();

		auto result = CredWriteW(&credential, 0);
	}

	bool CredentialManager::CredentialManageImp::Load(const std::string& credName, unsigned long credType)
	{
		AutoCredentialBuffer autoCredentialBuffer;
		mPopulated = false;
		if (0 != ::CredRead(std::wstring(credName.begin(), credName.end()).c_str(), static_cast<DWORD>(credType), 0, &autoCredentialBuffer.mPCREDENTIAL))
		{
			getCredContent(autoCredentialBuffer);
			mPopulated = true;
			return true;
		}
		else
		{
			return false;
		}
	}

	void CredentialManager::CredentialManageImp::getCredContent(const AutoCredentialBuffer& autoCredentialBuffer)
	{
		mCredName = CW2A(autoCredentialBuffer.mPCREDENTIAL->TargetName);
		mUserName = CW2A(autoCredentialBuffer.mPCREDENTIAL->UserName);
		mPersistence = autoCredentialBuffer.mPCREDENTIAL->Persist;
		mCredType = autoCredentialBuffer.mPCREDENTIAL->Type;
		mSecret = CW2A(reinterpret_cast<LPCWSTR>(autoCredentialBuffer.mPCREDENTIAL->CredentialBlob));
		
		////second method to covert lpbyte to string
		//int size_needed = WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<LPCWSTR>(autoCredentialBuffer.mPCREDENTIAL->CredentialBlob), autoCredentialBuffer.mPCREDENTIAL->CredentialBlobSize / 2, NULL, 0, NULL, NULL);
		//std::unique_ptr<char> secret(new char[size_needed]);
		//WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<LPCWSTR>(autoCredentialBuffer.mPCREDENTIAL->CredentialBlob), autoCredentialBuffer.mPCREDENTIAL->CredentialBlobSize / 2, secret.get(), size_needed, NULL, NULL);
		//mSecret = std::string(secret.get(), secret.get() + size_needed);
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CredentialManager::CredentialManager() : mImp(new CredentialManageImp()){}

	CredentialManager::CredentialManager(const std::string& credName, unsigned long credType) :mImp(new CredentialManageImp(credName, credType)) {}

	CredentialManager::~CredentialManager() { delete mImp; }

	bool CredentialManager::Load(const std::string& credName, unsigned long credType)
	{
		return mImp->Load(credName, credType);
	}

	bool CredentialManager::Populated() const 
	{ 
		return mImp->Populated(); 
	}

	bool CredentialManager::Exists() const 
	{
		return mImp->Exists();
	}

	void CredentialManager::SetCredName(const std::string& credName)
	{
		mImp->SetCredName(credName);
	}

	void CredentialManager::SetUserName(const std::string& userName)
	{
		mImp->SetUserName(userName);
	}

	void CredentialManager::SetSecret(const std::string& secret)
	{
		mImp->SetSecret(secret);
	}
	
	void CredentialManager::SetCredPersistence(unsigned long persistence)
	{
		mImp->SetCredPersistence(persistence);
	}

	void CredentialManager::SetCredType(unsigned long credType)
	{
		mImp->SetCredType(credType);
	}

	void CredentialManager::Save() const
	{
		mImp->Save();
	}

	bool CredentialManager::Delete(const std::string& credName, unsigned long credType);

}