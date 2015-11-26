#include "SimpleMessageWindow.h"
#include "SimpleMessageWindowExample.h"

#include <atlbase.h>
#include <atlconv.h>	 
#include <strsafe.h>
#include <Windows.h>
#include <tchar.h>    //string and other mapping macros
#include <string>
#include <vector>
#include <string>

#define IDM_OK			1002
#define SMW_H 90
#define SMW_W 160

#define ID_ITEMNAME 200

namespace WinApiTrial
{
	namespace
	{
		//define an unicode string type alias
		typedef std::basic_string<TCHAR> ustring;
		//=============================================================================
		//message processing function declarations
		INT_PTR CALLBACK DlgProc1(HWND, UINT, WPARAM, LPARAM);
		void OnCommand(const HWND, int, int, const HWND);
		INT_PTR initialDialog(const HWND, LPARAM);

		//non-message function declarations
		void AddControl(std::vector<WORD>&, DWORD, DWORD, short, short, short, short, DWORD,
						const std::wstring&, const std::wstring&, DWORD helpID = 0,
						DWORD extradata = 0);
		void AddString(std::vector<WORD>&, const std::wstring&);
		inline int ErrMsg(const ustring&);
		void WordAlign(std::vector<WORD>&);
		bool resizeControl(HWND hwnd, WPARAM wParam, LPARAM lParam);
		//message processing functions
		//=============================================================================

		bool WndProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
		{
			switch (Msg)
			{
				case WM_COMMAND:
				{
					switch (LOWORD(wParam))
					{
						case IDM_OK:
							//AutoBuffer<MAX_PASSWORD_BUFFER_LENGTH> newSecret1;
							//GetWindowText(GetDlgItem(hWnd, IDM_EDIT_OLD), oldSecretBuffer.mBuffer, MAX_PASSWORD_BUFFER_LENGTH);
							//GetWindowText(GetDlgItem(hWnd, IDM_EDIT_NEW_1), newSecret1.mBuffer, MAX_PASSWORD_BUFFER_LENGTH);
							//GetWindowText(GetDlgItem(hWnd, IDM_EDIT_NEW_2), newSecretBuffer.mBuffer, MAX_PASSWORD_BUFFER_LENGTH);
							//if (wcslen(oldSecretBuffer.mBuffer) == 0)
							//	popUpMsgWindow(ChangeSecret::ERR_MSG_TITLE, "The old password is empty.");
							//else if (wcslen(newSecret1.mBuffer) == 0)
							//	popUpMsgWindow(ChangeSecret::ERR_MSG_TITLE, "The new password is empty.");
							//else if (wcscmp(newSecret1.mBuffer, newSecretBuffer.mBuffer) != 0)
							//	popUpMsgWindow(ChangeSecret::ERR_MSG_TITLE, "The new passwords are not identical.");
							//else if (wcscmp(oldSecretBuffer.mBuffer, newSecret1.mBuffer) == 0)
							//	popUpMsgWindow(ChangeSecret::ERR_MSG_TITLE, "The old and new password can't be identical");
							//else
							//{
							//	DestroyWindow(hWnd);
							//}
							break;
					}
					break;
				}
				case WM_CLOSE:
				{
					//DestroyWindow(hWnd);
					break;
				}
				case WM_DESTROY:
				{
					//PostQuitMessage(WM_QUIT);
					break;
				}
				default:
					//return DefWindowProc(hWnd, Msg, wParam, lParam);
					break;
			}
			return 0;
		}
		INT_PTR CALLBACK DlgProc1(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			switch (uMsg)
			{
				case WM_COMMAND:
				{
					OnCommand(hwnd, LOWORD(wParam), HIWORD(wParam), reinterpret_cast<HWND>(lParam));
					return 0;
				}						 				
				case WM_SIZE:
				{
					std::cout << "resizing..." << std::endl;
					//resizeControl(hwnd, wParam, lParam);
					return 0;
				}

				case WM_INITDIALOG:
				{
					return initialDialog(hwnd, lParam);
				}
				default:
					return FALSE;  //let system deal with msg
			}
		}
		//=============================================================================
		void OnCommand(const HWND hwnd, int id, int notifycode, const HWND hCntrl)
		{
			//handles WM_COMMAND message of the modal dialogbox
			switch (id)
			{
				case IDOK:        //RETURN key pressed or 'ok' button selected
					std::cout << "OK" << std::endl;
					break;
				case IDCANCEL:    //ESC key pressed or 'cancel' button selected
					EndDialog(hwnd, id);
					break;
			}
		}
		//=============================================================================
		INT_PTR initialDialog(const HWND hwnd, LPARAM lParam)
		{
			HWND hwndOwner;
			RECT rc, rcDlg, rcOwner;

			// Get the owner window and dialog box rectangles. 

			if ((hwndOwner = GetParent(hwnd)) == NULL)
			{
				hwndOwner = GetDesktopWindow();
			}

			GetWindowRect(hwndOwner, &rcOwner);
			GetWindowRect(hwnd, &rcDlg);
			CopyRect(&rc, &rcOwner);

			// Offset the owner and dialog box rectangles so that right and bottom 
			// values represent the width and height, and then offset the owner again 
			// to discard space taken up by the dialog box. 

			OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top);
			OffsetRect(&rc, -rc.left, -rc.top);
			OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom);

			// The new position is the sum of half the remaining space and the owner's 
			// original position. 

			SetWindowPos(hwnd,
						 HWND_TOP,
						 rcOwner.left + (rc.right / 2),
						 rcOwner.top + (rc.bottom / 2),
						 0, 0,          // Ignores size arguments. 
						 SWP_NOSIZE);

			if (GetDlgCtrlID((HWND)lParam) != ID_ITEMNAME)
			{
				SetFocus(GetDlgItem(hwnd, ID_ITEMNAME));
				return FALSE;
			}
			return TRUE;

			//original one
			//set the small icon for the dialog. IDI_APPLICATION icon is set by default 
			//for winxp
			//SendMessage(hwnd, WM_SETICON, ICON_SMALL,
			//			reinterpret_cast<LPARAM>(LoadImage(0, IDI_APPLICATION, IMAGE_ICON,
			//			0, 0, LR_SHARED)));
			////ensure focus rectangle is properly drawn around control with focus
			//PostMessage(hwnd, WM_KEYDOWN, VK_TAB, 0);
			//return TRUE;
		}
		//=============================================================================
		//non-message processing functions
		//=============================================================================
		void AddControl(std::vector<WORD>& v, DWORD exStyle, DWORD style, short x, short y,
						short cx, short cy, DWORD id, const std::wstring& classname,
						const std::wstring& caption, DWORD helpID, DWORD extradata)
		{
			//add a control. defaults: helpID=0,extradata=0. Note there is no capability
			//in this function for dealing with non-zero values of extradata.
			WordAlign(v);

			v.push_back(LOWORD(helpID));
			v.push_back(HIWORD(helpID));

			v.push_back(LOWORD(exStyle));
			v.push_back(HIWORD(exStyle));

			v.push_back(LOWORD(style));
			v.push_back(HIWORD(style));

			v.push_back(x);  //left
			v.push_back(y);  //top
			v.push_back(cx); //width
			v.push_back(cy); //height

			//msdn docs are incorrect - the id is a DWORD value and not a WORD
			v.push_back(LOWORD(id));
			v.push_back(HIWORD(id));

			//there are only a few class atoms defined for standard (user) controls
			//so it's arguably better to use string class names than ordinals.
			AddString(v, classname.c_str());

			AddString(v, caption.c_str());

			v.push_back(0);  //no creation data 
		}
		//=============================================================================
		void AddString(std::vector<WORD>& v, const std::wstring& s)
		{
			//add a string to the array (eg. dialog title, control caption etc.)
			std::wstring::const_iterator iter;
			for (iter = s.begin(); iter != s.end(); ++iter)
			{
				v.push_back(*iter);
			}
			v.push_back(L'\0');
		}
		//=============================================================================
		inline int ErrMsg(const ustring& s)
		{
			return MessageBox(0, s.c_str(), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		}
		//=============================================================================
		void WordAlign(std::vector<WORD>& v)
		{
			//msdn states that controls must be added at dword boundary. This is incorrect;
			//controls must be WORD aligned.
			std::size_t size = v.size() % 2;

			for (unsigned int i = 0; i < size; ++i)
			{
				v.push_back(0);  //padding
			}
		}
		//=============================================================================


		void ErrorExit(LPTSTR lpszFunction)
		{
			// Retrieve the system error message for the last-error code

			LPVOID lpMsgBuf;
			LPVOID lpDisplayBuf;
			DWORD dw = GetLastError();

			FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				dw,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&lpMsgBuf,
				0, NULL);

			// Display the error message and exit the process

			lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
											  (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
			StringCchPrintf((LPTSTR)lpDisplayBuf,
							LocalSize(lpDisplayBuf) / sizeof(TCHAR),
							TEXT("%s failed with error %d: %s"),
							lpszFunction, dw, lpMsgBuf);
			MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

			LocalFree(lpMsgBuf);
			LocalFree(lpDisplayBuf);
			ExitProcess(dw);
		}

	} // namespace anonymous

	class SimpleMessageWindow::SimpleMessageWindowImp
	{
	public:
		SimpleMessageWindowImp(const std::string & messageOwner);

	private:
		HINSTANCE mHInstance;
		HWND mHWnd;
		WNDCLASSEX mWndClassEx;

		static const std::string mClassName;
		std::string mMessageOwner;

	};
	const std::string SimpleMessageWindow::SimpleMessageWindowImp::mClassName = "SimpleMessageWindowImp";

	SimpleMessageWindow::SimpleMessageWindowImp::SimpleMessageWindowImp(const std::string & messageOwner)
		:mMessageOwner(messageOwner)
	{
		USES_CONVERSION;

		// Create the application window
		// https://msdn.microsoft.com/en-us/library/windows/desktop/ms645398%28v=vs.85%29.aspx
		std::vector<WORD> aMemoryDlg;

		//setup the dialog template
		aMemoryDlg.push_back(1); // dialog version
		aMemoryDlg.push_back(0xffff); // extended dialog template

		// help ID
		DWORD helpID = 0;
		aMemoryDlg.push_back(LOWORD(helpID));
		aMemoryDlg.push_back(HIWORD(helpID));

		// The extended windows styles
		DWORD exStyle = 0;
		aMemoryDlg.push_back(LOWORD(exStyle));
		aMemoryDlg.push_back(HIWORD(exStyle));

		// The style of the control
		DWORD style = DS_CENTER | WS_OVERLAPPEDWINDOW | WS_POPUP | WS_VISIBLE | DS_SETFONT | DS_MODALFRAME;
		aMemoryDlg.push_back(LOWORD(style));
		aMemoryDlg.push_back(HIWORD(style));

		//The number of controls in the dialog box.
		aMemoryDlg.push_back(3);    

		
		aMemoryDlg.push_back(0);    // The x-coordinate, in dialog box units, of the upper-left corner of the dialog box.
		aMemoryDlg.push_back(0);    // The y-coordinate, in dialog box units, of the upper-left corner of the dialog box.
		aMemoryDlg.push_back(320);  // The width, in dialog box units, of the dialog box.
		aMemoryDlg.push_back(180);  // The height, in dialog box units, of the dialog box.

		aMemoryDlg.push_back(0);    // A variable-length array of 16-bit elements that identifies a menu resource for the dialog box
		aMemoryDlg.push_back(0);    // A variable-length array of 16-bit elements that identifies the window class of the dialog box

		// The title of the dialog box.
		std::wstring title = CA2W(("Message from " + mMessageOwner).c_str());
		AddString(aMemoryDlg, title);

		//The point size of the font to use for the text in the dialog box and its controls. 
		//Set font but only if DS_SETFONT or DS_SHELLFONT styles are set
		DWORD dwTest = style;
		if (dwTest & DS_SETFONT)
		{
			//this is for simplicity; it would probably be better to obtain and use the
			//respective properties of the default gui or system fonts
			aMemoryDlg.push_back(8);          //pointsize
			aMemoryDlg.push_back(FW_NORMAL);  //weight
			aMemoryDlg.push_back(MAKEWORD(0, DEFAULT_CHARSET));  //italic,charset
			AddString(aMemoryDlg, L"MS Sans Serif");
		}

		//add 'ok' button
		AddControl(aMemoryDlg,
				   0,
				   WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP,
				   22, 62, 50, 14,
				   IDOK,
				   L"button",
				   L"Ok");

		//add 'cancel' button           
		AddControl(aMemoryDlg,
				   0,
				   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
				   111, 62, 50, 14,
				   IDCANCEL,
				   L"button",
				   L"Cancel");

		//add an edit control
		AddControl(aMemoryDlg,
				   WS_EX_CLIENTEDGE,
				   WS_CHILD | WS_VISIBLE | WS_TABSTOP,
				   10, 10, 100, 14,
				   200,
				   L"edit",
				   L"single line edit control");


		//// Register the application
		//RegisterClassEx(&mWndClassEx);

		DLGTEMPLATE *pdt = reinterpret_cast<DLGTEMPLATE*>(&aMemoryDlg[0]);

		mHInstance = GetModuleHandle(NULL);
		auto a = DialogBoxIndirect(mHInstance, pdt, 0, DlgProc1);
		//auto a = CreateDialogIndirect(mHInstance, pdt, 0, DlgProc1);
		//ErrorExit(TEXT("DialogBoxIndirect"));
		SetFocus((HWND)mHWnd);
		if (!mHWnd) // If the window was not created,
			throw std::runtime_error("Can't create window."); //TODO: use KBase
	}

	SimpleMessageWindow::SimpleMessageWindow(const std::string & messageOwner)
		:mImp(new SimpleMessageWindowImp(messageOwner))
	{
	}

	SimpleMessageWindow::~SimpleMessageWindow()
	{
		delete mImp;
	}

} //namespace WinApiTrial

namespace
{
	void TestFunc1()
	{
		WinApiTrial::SimpleMessageWindow aWindow("WinAPI");
		std::cout << "Please enter a number:\n";
		long a;
		std::cin >> a;
	}

	void TestFunc_Example1()
	{
		std::cout << "SimpleMessageWindowExample::Example1();\n";
		SimpleMessageWindowExample::Example1();
	}

	void TestFunc_Example2()
	{
		SimpleMessageWindowExample::Example2();
	}

	void TestFunc_Example3()
	{
		std::cout << "SimpleMessageWindowExample::Example3();\n";
		SimpleMessageWindowExample::Example3();
	}

	void TestFunc_Example4()
	{
		std::cout << "SimpleMessageWindowExample::Example4();\n";
		SimpleMessageWindowExample::Example4();
	}

	void TestFunc_Example5()
	{
		std::cout << "SimpleMessageWindowExample::Example5();\n";
		SimpleMessageWindowExample::Example5();
	}
	void TestFunc_Example6()
	{
		std::cout << "SimpleMessageWindowExample::Example6();\n";
		SimpleMessageWindowExample::Example6();
	}


} // namespace anonymous

namespace CPP_STD_TEST_AND_PRACTIVE_TS
{
	using namespace boost::unit_test;
	test_suite* SimpleMessageWindowTS::suite()
	{
		test_suite* suite = BOOST_TEST_SUITE("SimpleMessageWindowTS");
		suite->add(BOOST_TEST_CASE(&TestFunc1));
		//suite->add(BOOST_TEST_CASE(&TestFunc_Example1));
		//suite->add(BOOST_TEST_CASE(&TestFunc_Example2));
		//suite->add(BOOST_TEST_CASE(&TestFunc_Example3));
		//suite->add(BOOST_TEST_CASE(&TestFunc_Example4));
		//suite->add(BOOST_TEST_CASE(&TestFunc_Example5));
		//suite->add(BOOST_TEST_CASE(&TestFunc_Example6));
		return suite;
	}
}

