#include "WinUtils.h"

#include <atlbase.h>

namespace KBaseWin 
{
	//TODO: maybe we have to decrypt source and convert it to BSTR
	BSTR toBSTR(int& wcharLength, const std::string& source)
	{
		wcharLength = ::MultiByteToWideChar(CP_UTF8, 0, source.data(), source.length(), NULL, 0);

		BSTR wcharData = ::SysAllocStringLen(NULL, wcharLength);
		::MultiByteToWideChar(CP_UTF8, 0, source.data(), source.length(),
			wcharData, wcharLength);
		return wcharData;

	}

	int popUpMsgWindow(const std::string& title, const std::string& errMsg, size_t msgType)
	{
		USES_CONVERSION;
		return MessageBox(NULL, A2CW(errMsg.c_str()), A2CW(title.c_str()), msgType);
	}
}