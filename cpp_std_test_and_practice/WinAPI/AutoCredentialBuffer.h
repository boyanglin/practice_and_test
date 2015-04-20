#ifndef AUTO_CREDENTIAL_BUFFER_H_
#define AUTO_CREDENTIAL_BUFFER_H_ 

#include <Windows.h>
#include <wincred.h>

namespace KBaseWin {

	struct AutoCredentialBuffer
	{

		AutoCredentialBuffer() :mPCREDENTIAL(0) 
		{

		}

		~AutoCredentialBuffer()
		{
			if (0 != mPCREDENTIAL)
			{
				if (mPCREDENTIAL->CredentialBlobSize > 0)
					::SecureZeroMemory(mPCREDENTIAL->CredentialBlob, mPCREDENTIAL->CredentialBlobSize);

				::CredFree(mPCREDENTIAL);

			}
		}

		PCREDENTIAL mPCREDENTIAL;

	private:

		AutoCredentialBuffer(const AutoCredentialBuffer&);
		AutoCredentialBuffer& operator=(const AutoCredentialBuffer&);
	};

} //KWin

#endif  //KWIN_KAUTOCREDENTIALBUFFER_H_