#ifndef WIN_UTILS_H_
#define WIN_UTILS_H_

#include <string>

namespace WinAPI {

	wchar_t* toLPWSTR(size_t& strSize, const std::string& strIn);

}

#endif