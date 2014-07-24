#ifndef KCREDENTIAL_MANAGER_H_
#define KCREDENTIAL_MANAGER_H_

#include <string>

namespace WinAPI {

	struct CredentialType 
	{
		static const unsigned long TypeNone;
		static const unsigned long Generic;
		static const unsigned long DomainPassword;
		static const unsigned long DomainCertificate;
		static const unsigned long DomainVisiblePassword;

		bool IsValid(unsigned long type)
		{
			return (type == TypeNone 
				|| type == Generic 
				|| type == DomainPassword 
				|| type == DomainCertificate 
				|| type == DomainVisiblePassword);
		}
	};

	struct CredentialPersistence
	{
		static const unsigned long PersistenceNone;
		static const unsigned long Session;
		static const unsigned long LocalComputer;
		static const unsigned long Enterprise;

		bool IsValid(unsigned long type)
		{
			return (type == PersistenceNone 
				|| type == Session 
				|| type == LocalComputer 
				|| type == Enterprise);
		}
	};

	class CredentialManager {
	public:
		CredentialManager();
		CredentialManager(const std::string& credName, unsigned long credtype);
		~CredentialManager();

		bool Load(const std::string& credName, unsigned long credType);

		bool Populated() const;
		bool Exists() const;

		void SetCredName(const std::string& credName);
		void SetUserName(const std::string& userName);
		void SetSecret(const std::string& password);
		void SetCredPersistence(unsigned long persistence);
		void SetCredType(unsigned long credType);

		void Save() const;
		static bool Delete(const std::string& credName, unsigned long credType);

	private:
		// no need to copy
		CredentialManager(const CredentialManager &);
		CredentialManager& operator=(const CredentialManager &) { return *this; }

		class CredentialManageImp;
		CredentialManageImp *mImp;
	};
}

#endif