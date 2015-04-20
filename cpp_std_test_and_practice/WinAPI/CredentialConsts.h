#ifndef CREDENTIAL_CONSTS_H_
#define CREDENTIAL_CONSTS_H_


namespace KBaseWin {
	struct CredentialType
	{
		static const unsigned long Generic;
		static const unsigned long DomainPassword;
		static const unsigned long DomainCertificate;
		static const unsigned long DomainVisiblePassword;

		static bool IsValid(unsigned long type)
		{
			return (type == Generic
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

		static bool IsValid(unsigned long type)
		{
			return (type == PersistenceNone
				|| type == Session
				|| type == LocalComputer
				|| type == Enterprise);
		}
	};
}

#endif