#include "ChangeCredential.h"

#include "AutoBuffer.h"
#include "CredentialPrompt.h"

#include <boost\lexical_cast.hpp>

#include "WinUtils.h"

#include <atlbase.h>
#include <wincred.h>
#include <Windows.h>

namespace KBaseWin {

#define IDM_OK     1002
#define IDM_CANCEL    1003

#define IDM_EDIT_OLD 1011
#define IDM_EDIT_NEW_1 1012
#define IDM_EDIT_NEW_2 1013

//#define CREDUI_MAX_PASSWORD_LENGTH  5 //for test only

	static const size_t MAX_PASSWORD_BUFFER_LENGTH = CREDUI_MAX_PASSWORD_LENGTH + 1;

	namespace {
		void checkPasswordLength(HWND hWnd, int IDM_TYPE)
		{
			if (GetWindowTextLengthW(GetDlgItem(hWnd, IDM_TYPE)) > CREDUI_MAX_PASSWORD_LENGTH) {
				static bool needHandle = true; //can't find a way to suppress events
				if (needHandle) {
					needHandle = false;
					popUpMsgWindow(ChangeCredential::ERR_MSG_TITLE, "The password can't be longer than " + boost::lexical_cast<std::string>(CREDUI_MAX_PASSWORD_LENGTH)+" characters.");
					SetWindowText(GetDlgItem(hWnd, IDM_TYPE), L"");
				}
				else
				{
					needHandle = true;
				}
			}
		}

		void clearEdits(HWND hWnd)
		{
			SetWindowText(GetDlgItem(hWnd, IDM_EDIT_OLD), L"");
			SetWindowText(GetDlgItem(hWnd, IDM_EDIT_NEW_1), L"");
			SetWindowText(GetDlgItem(hWnd, IDM_EDIT_NEW_2), L"");
		}
	} // namespace anonymous

	LRESULT WndProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		switch (Msg)
		{
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDM_CANCEL:
				clearEdits(hWnd);
				PostQuitMessage(WM_QUIT);
				break;
			case IDM_EDIT_OLD: 
				checkPasswordLength(hWnd, IDM_EDIT_OLD);
				break;
			case IDM_EDIT_NEW_1:
				checkPasswordLength(hWnd, IDM_EDIT_NEW_1);
				break;
			case IDM_EDIT_NEW_2:
				checkPasswordLength(hWnd, IDM_EDIT_NEW_2);
				break;
			case IDM_OK:
				AutoBuffer<MAX_PASSWORD_BUFFER_LENGTH> oldSecret, newSecret1, newSecret2;
				GetWindowText(GetDlgItem(hWnd, IDM_EDIT_OLD), oldSecret.mBuffer, MAX_PASSWORD_BUFFER_LENGTH);
				GetWindowText(GetDlgItem(hWnd, IDM_EDIT_NEW_1), newSecret1.mBuffer, MAX_PASSWORD_BUFFER_LENGTH);
				GetWindowText(GetDlgItem(hWnd, IDM_EDIT_NEW_2), newSecret2.mBuffer, MAX_PASSWORD_BUFFER_LENGTH);
				if (wcslen(oldSecret.mBuffer) == 0)
					popUpMsgWindow(ChangeCredential::ERR_MSG_TITLE, "The old password is empty.");
				else if (wcslen(newSecret1.mBuffer) == 0)
					popUpMsgWindow(ChangeCredential::ERR_MSG_TITLE, "The new password is empty.");
				else if (wcscmp(newSecret1.mBuffer, newSecret2.mBuffer) != 0)
					popUpMsgWindow(ChangeCredential::ERR_MSG_TITLE, "The new passwords are not identical.");
				else if (wcscmp(oldSecret.mBuffer, newSecret1.mBuffer) == 0)
					popUpMsgWindow(ChangeCredential::ERR_MSG_TITLE, "The old and new password can't be identical");
				else
				{
					int result = popUpMsgWindow(ChangeCredential::ERR_MSG_TITLE, "Do you want to save the new password?", MB_OKCANCEL | MB_ICONQUESTION);
					if (result == IDOK)
						PostQuitMessage(WM_QUIT);
				}
				break;
			}
			break;
		}
		case WM_CLOSE:
		{
			PostQuitMessage(WM_QUIT);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(WM_QUIT);
			break;
		}
		default:
			return DefWindowProc(hWnd, Msg, wParam, lParam);
			break;
		}
		return 0;
	}

	const wchar_t* const ChangeCredential::CLASS_NAME = L"ChangeCredential";
	const char* const ChangeCredential::ERR_MSG_TITLE = "Kaprisk Message";

	ChangeCredential::ChangeCredential(const std::string& credName) 
	{
		mHInstance = GetModuleHandle(NULL);
		createWNDCLASSEX();
		addBtn_OK();
		addBtn_Cancel();
		addLabel_OldSecret();
		addLabel_NewSecret1();
		addLabel_NewSecret2();
		addTextBox_Oldsecret();
		addTextBox_NewSecret1();
		addTextBox_NewSecret2();
	}

	void ChangeCredential::addBtn_OK()
	{
		HWND aHButton;
		aHButton = ::CreateWindow(L"BUTTON",
								  L"ok",
								  WS_CHILD | WS_VISIBLE | SS_LEFT,
								  BTN_OK_L, 
								  BTN_OK_T, 
								  BTN_OK_W, 
								  BTN_OK_H,
								  mHWnd, 
								  (HMENU)(IDM_OK),
								  mHInstance, 
								  NULL);
		if (!aHButton)
		{
			throw std::exception("Failed to create controls"); //TODO: use KBase
		}
	}

	void ChangeCredential::addBtn_Cancel()
	{
		HWND aHButton;
		aHButton = ::CreateWindow(L"BUTTON",
								  L"cancel",
								  WS_CHILD | WS_VISIBLE | SS_LEFT,
								  BTN_CANCEL_L, 
								  BTN_CANCEL_T, 
								  BTN_CANCEL_W, 
								  BTN_CANCEL_H,
								  mHWnd, 
								  (HMENU)IDM_CANCEL, 
								  mHInstance, 
								  NULL);
		if (!aHButton)
		{
			throw std::exception("Failed to create controls"); //TODO: use KBase
		}
	}

	void ChangeCredential::addLabel_OldSecret()
	{
		HWND aHLabel;
		aHLabel = ::CreateWindow(L"STATIC",
								 L"enter old password",
								 WS_CHILD | WS_VISIBLE | SS_LEFT,
								 STATIC_OLD_SECRET_L, 
								 STATIC_OLD_SECRET_T, 
								 STATIC_OLD_SECRET_W, 
								 STATIC_OLD_SECRET_H,
								 mHWnd,
								 NULL,
								 mHInstance, 
								 NULL);
		if (aHLabel == NULL)
		{
			throw std::exception("Failed to create controls"); //TODO: use KBase
		}
	}

	void ChangeCredential::addLabel_NewSecret1()
	{
		HWND aHLabel;
		aHLabel = ::CreateWindow(L"STATIC",
								 L"enter new password",
								 WS_CHILD | WS_VISIBLE | SS_LEFT,
								 STATIC_NEW_SECRET1_L,
								 STATIC_NEW_SECRET1_T,
								 STATIC_NEW_SECRET1_W,
								 STATIC_NEW_SECRET1_H,
								 mHWnd,
								 NULL,
								 mHInstance,
								 NULL);
		if (!aHLabel)
		{
			throw std::exception("Failed to create controls"); //TODO: use KBase
		}

	}

	void ChangeCredential::addLabel_NewSecret2()
	{
		HWND aHLabel;
		aHLabel = ::CreateWindow(L"STATIC",
								 L"confirm new password",
								 WS_CHILD | WS_VISIBLE | SS_LEFT,
								 STATIC_NEW_SECRET2_L, 
								 STATIC_NEW_SECRET2_T, 
								 STATIC_NEW_SECRET2_W, 
								 STATIC_NEW_SECRET2_H,
								 mHWnd, 
								 NULL,
								 mHInstance, 
								 NULL);
		if (!aHLabel)
		{
			throw std::exception("Failed to create controls"); //TODO: use KBase
		}
		//setFont(aHLabel);
	}

	void ChangeCredential::addTextBox_Oldsecret()
	{
		HWND aHTextBox;
		aHTextBox = ::CreateWindow( L"EDIT",
									L"",
									WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_PASSWORD | SS_SUNKEN,
									EDIT_OLD_SECRET_L, 
									EDIT_OLD_SECRET_T, 
									EDIT_OLD_SECRET_W, 
									EDIT_OLD_SECRET_H,
									mHWnd, 
									(HMENU)IDM_EDIT_OLD,
									mHInstance, 
									NULL);
		if (aHTextBox == NULL)
		{
			throw std::exception("Failed to create controls"); //TODO: use KBase
		}
	}

	void ChangeCredential::addTextBox_NewSecret1()
	{
		HWND aHTextBox;
		aHTextBox = ::CreateWindow( L"EDIT",
									L"",
									WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_PASSWORD | SS_SUNKEN,
									EDIT_NEW_SECRET1_L, 
									EDIT_NEW_SECRET1_T, 
									EDIT_NEW_SECRET1_W, 
									EDIT_NEW_SECRET1_H,
									mHWnd, 
									(HMENU)IDM_EDIT_NEW_1,
									mHInstance, 
									NULL);
		if (!aHTextBox)
		{
			throw std::exception("Failed to create controls"); //TODO: use KBase
		}
	}

	void ChangeCredential::addTextBox_NewSecret2()
	{
		HWND aHTextBox;
		aHTextBox = ::CreateWindow( L"EDIT",
									L"",
									WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_PASSWORD | SS_SUNKEN,
									EDIT_NEW_SECRET2_L,
									EDIT_NEW_SECRET2_T,
									EDIT_NEW_SECRET2_W,
									EDIT_NEW_SECRET2_H,
									mHWnd,
									(HMENU)IDM_EDIT_NEW_2,
									mHInstance,
									NULL);
		if(!aHTextBox)
		{
			throw std::exception("Failed to create controls"); //TODO: use KBase
		}
	}

	void ChangeCredential::createWNDCLASSEX()
	{
		// Create the application window
		mWndClassEx.cbSize = sizeof(WNDCLASSEX);
		mWndClassEx.style = CS_HREDRAW | CS_VREDRAW;
		mWndClassEx.lpfnWndProc = (WNDPROC)(WndProcedure); //TODO: add process to handle user return
		mWndClassEx.cbClsExtra = 0;
		mWndClassEx.cbWndExtra = 0;
		mWndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		mWndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
		mWndClassEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		mWndClassEx.lpszMenuName = NULL;
		mWndClassEx.lpszClassName = CLASS_NAME;
		mWndClassEx.hInstance = mHInstance;
		mWndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		// Register the application
		RegisterClassEx(&mWndClassEx);		
		
		mHWnd = ::CreateWindow( CLASS_NAME,
								L"Calling a Dialog Box From an SDI",
								WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU /*| WS_MINIMIZEBOX | WS_MAXIMIZEBOX*/,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								WND_W,
								WND_H,
								NULL,
								NULL,
								mHInstance,
								NULL);

		if (!mHWnd) // If the window was not created,
			throw std::runtime_error("Can't create window."); //TODO: use KBase
	}


	bool ChangeCredential::PopupWindow()
	{
		ShowWindow(mHWnd, SW_SHOWNORMAL);
		UpdateWindow(mHWnd);

		MSG Msg;
		// Decode and treat the messages
		// as long as the application is running
		while (GetMessage(&Msg, NULL, 0, 0))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		AutoBuffer<MAX_PASSWORD_BUFFER_LENGTH> oldSecretBuffer, newSecretBuffer;
		GetWindowText(GetDlgItem(mHWnd, IDM_EDIT_OLD), oldSecretBuffer.mBuffer, MAX_PASSWORD_BUFFER_LENGTH);
		GetWindowText(GetDlgItem(mHWnd, IDM_EDIT_NEW_2), newSecretBuffer.mBuffer, MAX_PASSWORD_BUFFER_LENGTH);

		if (wcslen(oldSecretBuffer.mBuffer) > 0 && wcslen(newSecretBuffer.mBuffer) > 0)
		{
			//TODO: encrypt
			mOldSecret = CW2A(oldSecretBuffer.mBuffer);
			mNewSecret = CW2A(newSecretBuffer.mBuffer);
			return true;
		}
		else
		{
			return false;
		}
		
	}
}