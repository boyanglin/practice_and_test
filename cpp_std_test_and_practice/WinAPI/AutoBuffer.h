#ifndef AUTO_PASSWORD_BUFFER_H_
#define AUTO_PASSWORD_BUFFER_H_

#include <Windows.h>

template <typename int Length>
class AutoBuffer
{
public:
	AutoBuffer()
	{
		::ZeroMemory(mBuffer, sizeof (Length));
	}

	~AutoBuffer()
	{
		::SecureZeroMemory(mBuffer, sizeof (Length));
	}

	wchar_t mBuffer[Length];

};

#endif //AUTO_PASSWORD_BUFFER_H_