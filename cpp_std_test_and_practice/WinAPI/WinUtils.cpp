#include "WinUtils.h"
#include <atlconv.h>

namespace WinAPI 
{
	wchar_t* toLPWSTR(size_t& strSizeOut, const std::string& strIn)
	{
		strSizeOut = static_cast<size_t>(MultiByteToWideChar(CP_UTF8, 0, strIn.c_str(), -1, NULL, 0));
		wchar_t* strOut = new wchar_t[strSizeOut];
		MultiByteToWideChar(CP_UTF8, 0, strIn.c_str(), -1, strOut, strSizeOut);
		return strOut;
	}
}