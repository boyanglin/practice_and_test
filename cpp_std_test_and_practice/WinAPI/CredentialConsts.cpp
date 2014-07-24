#include "CredentialConsts.h"

#include <Windows.h>
#include <wincred.h>

namespace WinAPI {

	const unsigned long CredentialType::Generic = CRED_TYPE_GENERIC;
	const unsigned long CredentialType::DomainPassword = CRED_TYPE_DOMAIN_PASSWORD;
	const unsigned long CredentialType::DomainCertificate = CRED_TYPE_DOMAIN_CERTIFICATE;
	const unsigned long CredentialType::DomainVisiblePassword = CRED_TYPE_DOMAIN_VISIBLE_PASSWORD;

	const unsigned long CredentialPersistence::PersistenceNone = CRED_PERSIST_NONE;
	const unsigned long CredentialPersistence::Session = CRED_PERSIST_SESSION;
	const unsigned long CredentialPersistence::LocalComputer = CRED_PERSIST_LOCAL_MACHINE;
	const unsigned long CredentialPersistence::Enterprise = CRED_PERSIST_ENTERPRISE;

} //namespace WinAPI
