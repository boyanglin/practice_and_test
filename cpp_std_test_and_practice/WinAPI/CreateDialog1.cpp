#include <windows.h>

#include "CreateDialog1.h" 

const char g_szClassName[] = "myWindowClass";

HWND g_hToolbar = NULL;

namespace
{
	BOOL CALLBACK ToolDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		switch (Message)
		{
			case WM_COMMAND:
				switch (LOWORD(wParam))
				{
					case IDC_PRESS:
						MessageBox(hwnd, L"Hi!", L"This is a message",
								   MB_OK | MB_ICONEXCLAMATION);
						break;
					case IDC_OTHER:
						MessageBox(hwnd, L"Bye!", L"This is also a message",
								   MB_OK | MB_ICONEXCLAMATION);
						break;
				}
				break;
			default:
				return FALSE;
		}
		return TRUE;
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		switch (Message)
		{
			case WM_CREATE:
				g_hToolbar = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TOOLBAR),
										  hwnd, ToolDlgProc);
				if (g_hToolbar != NULL)
				{
					ShowWindow(g_hToolbar, SW_SHOW);
				}
				else
				{
					MessageBox(hwnd, L"CreateDialog returned NULL", L"Warning!",
							   MB_OK | MB_ICONINFORMATION);
				}
				break;
			case WM_COMMAND:
				switch (LOWORD(wParam))
				{
					case ID_FILE_EXIT:
						PostMessage(hwnd, WM_CLOSE, 0, 0);
						break;
					case ID_DIALOG_SHOW:
						ShowWindow(g_hToolbar, SW_SHOW);
						break;
					case ID_DIALOG_HIDE:
						ShowWindow(g_hToolbar, SW_HIDE);
						break;
				}
				break;
			case WM_CLOSE:
				DestroyWindow(hwnd);
				break;
			case WM_DESTROY:
				DestroyWindow(g_hToolbar);
				PostQuitMessage(0);
				break;
			default:
				return DefWindowProc(hwnd, Message, wParam, lParam);
		}
		return 0;
	}

}


namespace WinApiTrial
{ 
	int CreateDialog1()
	{
		WNDCLASSEX wc;
		HWND hwnd;
		MSG Msg;

		HINSTANCE hInstance = GetModuleHandle(NULL);
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = 0;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);
		wc.lpszClassName = (LPCWSTR)g_szClassName;
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&wc))
		{
			MessageBox(NULL, L"Window Registration Failed!", L"Error!",
					   MB_ICONEXCLAMATION | MB_OK);
			return 0;
		}

		hwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			(LPCWSTR)g_szClassName,
			L"The title of my window",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
			NULL, NULL, hInstance, NULL);

		if (hwnd == NULL)
		{
			MessageBox(NULL, L"Window Creation Failed!", L"Error!",
					   MB_ICONEXCLAMATION | MB_OK);
			return 0;
		}

		ShowWindow(hwnd, SW_SHOWNORMAL);
		UpdateWindow(hwnd);

		while (GetMessage(&Msg, NULL, 0, 0) > 0)
		{
			if (!IsDialogMessage(g_hToolbar, &Msg))
			{
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
		}
		return Msg.wParam;
	}
}

namespace CPP_STD_TEST_AND_PRACTIVE_TS
{
	using namespace boost::unit_test;
	test_suite* CreateDialog1TS::suite()
	{
		test_suite* suite = BOOST_TEST_SUITE("CreateDialog1TS");
		suite->add(BOOST_TEST_CASE(&WinApiTrial::CreateDialog1));
		return suite;
	}
}
