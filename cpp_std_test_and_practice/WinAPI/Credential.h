#ifndef KCREDENTIAL_MANAGER_H_
#define KCREDENTIAL_MANAGER_H_

#include <string>

namespace KBaseWin {

	class Credential {
	public:
		Credential();
		Credential(const std::string& credName, unsigned long credtype);
		~Credential();

		bool Load(const std::string& credName, unsigned long credType);

		bool Populated() const { return mPopulated; }
		bool Exists() const { return mPopulated; }

		void SetCredName(const std::string& credName);
		void SetUserName(const std::string& userName);
		void SetSecret(const std::string& password);
		void SetCredPersistence(unsigned long persistence);
		void SetCredType(unsigned long credType);

		std::string GetCredName() const { return mCredName; }
		std::string GetUsername() const { return mUsername; }
		std::string GetSecret() const { return mSecret; }
		unsigned long GetCredType() const { return mCredType; }
		unsigned long GetCredPersistence() const { return mPersistence; }

		void Save() const;
		static bool Delete(const std::string& credName, unsigned long credType);

	private:
		// no need to copy
		Credential(const Credential &);
		Credential& operator=(const Credential &) { return *this; }

		std::string mCredName;
		std::string mUsername;
		std::string mSecret; //TODO: this member variable should always contain encrypted text
		unsigned long mCredType;
		unsigned long mPersistence;

		bool mPopulated;

		bool exists(const std::string& credName, unsigned long credType);

		bool isContentValid() const;
	};
} //namespace KBaseWin 

#endif