#ifndef AUTO_PASSWORD_BSTR_H_
#define AUTO_PASSWORD_BSTR_H_

#include <string>
#include <Windows.h>

#include "WinUtils.h"

namespace KBaseWin {
	class AutoWStr
	{
	public:

		AutoWStr() :
			mWString(0)
		{
			// Do nothing
		}

		~AutoWStr()
		{
			SecureFreeString(mWString);
		}

		void Set(std::wstring* wstring)
		{
			SecureFreeString(mWString);
			mWString = wstring;
		}

		std::wstring* Get()
		{
			return mWString;
		}

	private:

		std::wstring* mWString;

		AutoWStr(const AutoWStr&);
		AutoWStr& operator=(const AutoWStr&);
	};

	//class AutoBstr
	//{
	//public:

	//	AutoBstr() :
	//		mBstr(0)
	//	{
	//		// Do nothing
	//	}

	//	~AutoBstr()
	//	{
	//		SecureFree();
	//	}

	//	void Set(BSTR bstr)
	//	{
	//		SecureFree();
	//		mBstr = bstr;
	//	}

	//	BSTR Get()
	//	{
	//		return mBstr;
	//	}

	//	void SecureFree()
	//	{
	//		if (0 != mBstr)
	//		{
	//			::SecureZeroMemory(mBstr, ::SysStringByteLen(mBstr));
	//			::SysFreeString(mBstr);
	//		}
	//	}
	//private:

	//	BSTR mBstr;

	//	AutoBstr(const AutoBstr&);
	//	AutoBstr& operator=(const AutoBstr&);
	//};
}

#endif //AUTO_PASSWORD_BSTR_H_