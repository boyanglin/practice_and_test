#ifndef AUTO_STD_STRING_H_
#define AUTO_STD_STRING_H_

#include <string>

#include "WinUtils.h"

namespace KBaseWin {

	class AutoStdString {
	public:
		AutoStdString(std::string* sourceString) : mString(sourceString) {}
		AutoStdString() : mString(nullptr) {}

		~AutoStdString()
		{
			SecureFreeString(mString);
		}

		void Set(std::string* sourceString)
		{
			SecureFreeString(mString);
			mString = sourceString;
		}

	private:
		std::string* mString;
	};

} //namespace KBaseWin

#endif