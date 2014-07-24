#include "WinUtils.h"


namespace WinAPI 
{
	BSTR toBSTR(int& wcharLength, const std::string& source)
	{
		wcharLength = ::MultiByteToWideChar(CP_UTF8, 0 /* no flags */,
			source.data(), source.length(),
			NULL, 0);

		BSTR wcharData = ::SysAllocStringLen(NULL, wcharLength);
		::MultiByteToWideChar(CP_ACP, 0 /* no flags */,
			source.data(), source.length(),
			wcharData, wcharLength);
		return wcharData;
	}
}