#ifndef WIN_UTILS_H_
#define WIN_UTILS_H_

#include <string>
#include <WTypes.h>

namespace WinAPI {

	//from std::string to wchar_t*
	BSTR toBSTR(int& wcharLength, const std::string& source);

}

#endif