#ifndef WIN_UTILS_H_
#define WIN_UTILS_H_

#include <string>
#include <Windows.h>

namespace KBaseWin {

	//from std::string to wchar_t*
	BSTR toBSTR(int& wcharLength, const std::string& source);

	template<class T>
	void SecureFreeString(T* target)
	{
		if (target != nullptr)
		{
			std::fill(target->begin(), target->end(), 0);
			target->clear();
		}
	}

	int popUpMsgWindow(const std::string& title, const std::string& errMsg, size_t msgType = MB_OK | MB_ICONERROR);
}

#endif