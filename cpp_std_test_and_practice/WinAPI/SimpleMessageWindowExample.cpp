#include "SimpleMessageWindowExample.h"

#include <atlconv.h>
#include <CommDlg.h>
#include <tchar.h>    //string and other mapping macros
#include <Windows.h>

#include <fstream>
#include <iostream>
#include <vector>


namespace SimpleMessageWindowExample
{
	// ***********************SimpleMessageWindowExample1********************************//
	namespace
	{
		//define an unicode string type alias
		typedef std::basic_string<TCHAR> ustring;
		//=============================================================================
		//message processing function declarations
		INT_PTR CALLBACK DlgProc1(HWND, UINT, WPARAM, LPARAM);
		void OnCommand(const HWND, int, int, const HWND);
		INT_PTR OnInitDlg(const HWND, LPARAM);

		//non-message function declarations
		void AddControl(std::vector<WORD>&, DWORD, DWORD, short, short, short, short, DWORD,
						const std::wstring&, const std::wstring&, DWORD helpID = 0,
						DWORD extradata = 0);
		void AddString(std::vector<WORD>&, const std::wstring&);
		inline int ErrMsg(const ustring&);
		void WordAlign(std::vector<WORD>&);
		//message processing functions
		//=============================================================================
		INT_PTR CALLBACK DlgProc1(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			switch (uMsg)
			{
				case WM_COMMAND:
				{
					OnCommand(hwnd, LOWORD(wParam), HIWORD(wParam),
							  reinterpret_cast<HWND>(lParam));
					return 0;
				}
				case WM_INITDIALOG:
				{
					return OnInitDlg(hwnd, lParam);
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
				case IDCANCEL:    //ESC key pressed or 'cancel' button selected
					EndDialog(hwnd, id);
			}
		}
		//=============================================================================
		INT_PTR OnInitDlg(const HWND hwnd, LPARAM lParam)
		{
			//set the small icon for the dialog. IDI_APPLICATION icon is set by default 
			//for winxp
			SendMessage(hwnd, WM_SETICON, ICON_SMALL,
						reinterpret_cast<LPARAM>(LoadImage(0, IDI_APPLICATION, IMAGE_ICON,
						0, 0, LR_SHARED)));
			//ensure focus rectangle is properly drawn around control with focus
			PostMessage(hwnd, WM_KEYDOWN, VK_TAB, 0);
			return TRUE;
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
	} // namespace anonymous 

	int Example1()
	{
		HINSTANCE hInst = GetModuleHandle(NULL);
		std::vector<WORD> memdlg;

		//setup the dialog template
		memdlg.push_back(1);
		memdlg.push_back(0xffff);

		DWORD helpID = 0;
		memdlg.push_back(LOWORD(helpID));
		memdlg.push_back(HIWORD(helpID));

		DWORD exStyle = 0;
		memdlg.push_back(LOWORD(exStyle));
		memdlg.push_back(HIWORD(exStyle));

		DWORD style = DS_CENTER | WS_OVERLAPPEDWINDOW | WS_POPUP | WS_VISIBLE | DS_SETFONT;
		memdlg.push_back(LOWORD(style));
		memdlg.push_back(HIWORD(style));

		memdlg.push_back(3);    //number of controls

		memdlg.push_back(0);    //left
		memdlg.push_back(0);    //top
		memdlg.push_back(186);  //width
		memdlg.push_back(93);   //height

		memdlg.push_back(0);    //no menu
		memdlg.push_back(0);    //standard system dialog box class

		//add dialogbox title
		AddString(memdlg, L"Dialog: Memory Template");

		//set font but only if DS_SETFONT or DS_SHELLFONT styles are set
		DWORD dwTest = style;
		if (dwTest & DS_SETFONT)
		{
			//this is for simplicity; it would probably be better to obtain and use the
			//respective properties of the default gui or system fonts
			memdlg.push_back(8);          //pointsize
			memdlg.push_back(FW_NORMAL);  //weight

			memdlg.push_back(MAKEWORD(0, DEFAULT_CHARSET));  //italic,charset

			AddString(memdlg, L"MS Sans Serif");
		}

		//add 'ok' button
		AddControl(memdlg,
				   0,
				   WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP,
				   22, 62, 50, 14,
				   IDOK,
				   L"button",
				   L"Ok");

		//add 'cancel' button           
		AddControl(memdlg,
				   0,
				   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
				   111, 62, 50, 14,
				   IDCANCEL,
				   L"button",
				   L"Cancel");

		//add an edit control
		AddControl(memdlg,
				   WS_EX_CLIENTEDGE,
				   WS_CHILD | WS_VISIBLE | WS_TABSTOP,
				   10, 10, 100, 14,
				   200,
				   L"edit",
				   L"single line edit control");

		//create the dialog  
		DLGTEMPLATE *pdt = reinterpret_cast<DLGTEMPLATE*>(&memdlg[0]);

		auto success1 = DialogBoxIndirect(hInst, pdt, 0, DlgProc1);
		//auto success2 = CreateDialogIndirect(hInst, pdt, 0, DlgProc1);

		SetFocus((HWND)success1);
		//SetFocus(success2);
		//if (success == -1)
		//{
		//	ErrMsg(_T("DialogBoxIndirect failed"));
		//}

		long i;
		std::cout << "Enter something to continue:\n";
		std::cin >> i;
		return 0;
	}

	// ***************************************************************//

	// ***********************Example2********************************//
	namespace
	{
#define ID_HELP   150
#define ID_TEXT   200
		//extern void WindowsMessageToString(char* Output, unsigned int Size, UINT Message, WPARAM wParam, LPARAM lParam);
		std::ofstream dlgfile, winfile;
		INT_PTR CALLBACK DlgProc2(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
		{
			char a[256];
			int Mod = sprintf_s(a, 256, "0x%08X: ", hwndDlg);
			//WindowsMessageToString(a + Mod, 256 - Mod, uMsg, wParam, lParam);
			dlgfile << a << std::endl;
			return FALSE;
		}
		LRESULT WinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
		{
			char a[256];
			int Mod = sprintf_s(a, 256, "0x%08X: ", hWnd);
			//WindowsMessageToString(a + Mod, 256 - Mod, Msg, wParam, lParam);
			winfile << a << std::endl;
			return DefWindowProc(hWnd, Msg, wParam, lParam);
		}

		LPWORD lpwAlign(LPWORD lpIn)
		{
			ULONG ul;

			ul = (ULONG)lpIn;
			ul++;
			ul >>= 1;
			ul <<= 1;
			return (LPWORD)ul;
		}

		LRESULT DisplayMyMessage(HINSTANCE hinst, HWND hwndOwner,
								 LPSTR lpszMessage)
		{
			HGLOBAL hgbl;
			LPDLGTEMPLATE lpdt;
			LPDLGITEMTEMPLATE lpdit;
			LPWORD lpw;
			LPWSTR lpwsz;
			LRESULT ret;
			int nchar;

			hgbl = GlobalAlloc(GMEM_ZEROINIT, 1024);
			if (!hgbl)
				return -1;

			lpdt = (LPDLGTEMPLATE)GlobalLock(hgbl);

			// Define a dialog box.

			lpdt->style = WS_POPUP | WS_BORDER | WS_SYSMENU
				| DS_MODALFRAME | WS_CAPTION;
			lpdt->cdit = 3;  // number of controls
			lpdt->x = 10;  lpdt->y = 10;
			lpdt->cx = 100; lpdt->cy = 100;

			lpw = (LPWORD)(lpdt + 1);
			*lpw++ = 0;   // no menu
			*lpw++ = 0;   // predefined dialog box class (by default)

			lpwsz = (LPWSTR)lpw;
			nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "My Dialog",
											-1, lpwsz, 50);
			lpw += nchar;

			//-----------------------
			// Define an OK button.
			//-----------------------
			lpw = lpwAlign(lpw); // align DLGITEMTEMPLATE on DWORD boundary
			lpdit = (LPDLGITEMTEMPLATE)lpw;
			lpdit->x = 10; lpdit->y = 70;
			lpdit->cx = 80; lpdit->cy = 20;
			lpdit->id = IDOK;  // OK button identifier
			lpdit->style = WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON;

			lpw = (LPWORD)(lpdit + 1);
			*lpw++ = 0xFFFF;
			*lpw++ = 0x0080;    // button class

			lpwsz = (LPWSTR)lpw;
			nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "OK", -1, lpwsz, 50);
			lpw += nchar;
			lpw = lpwAlign(lpw); // align creation data on DWORD boundary
			*lpw++ = 0;           // no creation data

			//-----------------------
			// Define a Help button.
			//-----------------------
			lpw = lpwAlign(lpw); // align DLGITEMTEMPLATE on DWORD boundary
			lpdit = (LPDLGITEMTEMPLATE)lpw;
			lpdit->x = 55; lpdit->y = 10;
			lpdit->cx = 40; lpdit->cy = 20;
			lpdit->id = ID_HELP;    // Help button identifier
			lpdit->style = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;

			lpw = (LPWORD)(lpdit + 1);
			*lpw++ = 0xFFFF;
			*lpw++ = 0x0080;                 // button class atom

			lpwsz = (LPWSTR)lpw;
			nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "Help", -1, lpwsz, 50);
			lpw += nchar;
			lpw = lpwAlign(lpw); // align creation data on DWORD boundary
			*lpw++ = 0;           // no creation data

			//-----------------------
			// Define a static text control.
			//-----------------------
			lpw = lpwAlign(lpw); // align DLGITEMTEMPLATE on DWORD boundary
			lpdit = (LPDLGITEMTEMPLATE)lpw;
			lpdit->x = 10; lpdit->y = 10;
			lpdit->cx = 40; lpdit->cy = 20;
			lpdit->id = ID_TEXT;  // text identifier
			lpdit->style = WS_CHILD | WS_VISIBLE | SS_LEFT;

			lpw = (LPWORD)(lpdit + 1);
			*lpw++ = 0xFFFF;
			*lpw++ = 0x0082;                         // static class

			for (lpwsz = (LPWSTR)lpw;
				 *lpwsz++ = (WCHAR)*lpszMessage++;
				 );
			lpw = (LPWORD)lpwsz;
			lpw = lpwAlign(lpw); // align creation data on DWORD boundary
			*lpw++ = 0;           // no creation data

			GlobalUnlock(hgbl);
			ret = DialogBoxIndirect(hinst, (LPDLGTEMPLATE)hgbl,
									hwndOwner, (DLGPROC)DlgProc2); //Erzengeldeslichtes: I modified this line to change DialogProc to DlgProc.
			GlobalFree(hgbl);
			return ret;
		}
	} // namespace anonymous

	int Example2()
	{
		winfile.open("WinMessages.txt");
		dlgfile.open("DlgMessages.txt");
		HINSTANCE hInstance = GetModuleHandle(NULL);
		//DialogBoxIndirect in the example SHOULD have its own little message pump so IF it's displayed, 
		//	it will stay displayed until a button is clicked. Then we can quit.
		return DisplayMyMessage(hInstance, 0, "Test");
	}
	// ***************************************************************//

	// ***********************Example3********************************//
	namespace
	{
#define GET_WM_COMMAND_ID(wp, lp) LOWORD(wp) //http://www.dreamincode.net/forums/topic/286954-using-windowsxh-for-better-code-organization-and-message-cracking/
		INT_PTR CALLBACK DlgProc(HWND hwnd, UINT wm, WPARAM wParam, LPARAM lParam)
		{
			switch (wm)
			{
				case WM_INITDIALOG: return TRUE;
				case WM_COMMAND:
					if (GET_WM_COMMAND_ID(wParam, lParam) == IDCANCEL) EndDialog(hwnd, 0);
					break;
			}
			return FALSE;
		}

		class DialogTemplate
		{
		public:
			LPCDLGTEMPLATE Template() { return (LPCDLGTEMPLATE)&v[0]; }
			void AlignToDword()
			{
				if (v.size() % 4) Write(NULL, 4 - (v.size() % 4));
			}
			void Write(LPCVOID pvWrite, DWORD cbWrite)
			{
				v.insert(v.end(), cbWrite, 0);
				if (pvWrite) CopyMemory(&v[v.size() - cbWrite], pvWrite, cbWrite);
			}
			template<typename T> void Write(T t) { Write(&t, sizeof(T)); }
			void WriteString(LPCWSTR psz)
			{
				Write(psz, (lstrlenW(psz) + 1) * sizeof(WCHAR));
			}

		private:
			std::vector<BYTE> v;
		};

		BOOL FakeMessageBox()
		{
			LPCWSTR pszMessage = L"This is a FakeMessageBox example.";
			LPCWSTR pszTitle = L"FakeMessageBox";
			BOOL fSuccess = FALSE;
			HDC hdc = GetDC(NULL);
			if (hdc)
			{
				NONCLIENTMETRICSW ncm = { sizeof(ncm) };
				if (SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, 0, &ncm, 0))
				{
					DialogTemplate tmp;

					// Write out the extended dialog template header
					tmp.Write<WORD>(1); // dialog version
					tmp.Write<WORD>(0xFFFF); // extended dialog template
					tmp.Write<DWORD>(0); // help ID
					tmp.Write<DWORD>(0); // extended style
					tmp.Write<DWORD>(WS_CAPTION | WS_SYSMENU | DS_SETFONT | DS_MODALFRAME);
					tmp.Write<WORD>(2); // number of controls
					tmp.Write<WORD>(32); // X
					tmp.Write<WORD>(32); // Y
					tmp.Write<WORD>(200); // width
					tmp.Write<WORD>(80); // height
					tmp.WriteString(L""); // no menu
					tmp.WriteString(L""); // default dialog class
					tmp.WriteString(pszTitle); // title

					// Next comes the font description.
					// See text for discussion of fancy formula.
					if (ncm.lfMessageFont.lfHeight < 0)
					{
						ncm.lfMessageFont.lfHeight = -MulDiv(ncm.lfMessageFont.lfHeight,
															 72, GetDeviceCaps(hdc, LOGPIXELSY));
					}
					tmp.Write<WORD>((WORD)ncm.lfMessageFont.lfHeight); // point
					tmp.Write<WORD>((WORD)ncm.lfMessageFont.lfWeight); // weight
					tmp.Write<BYTE>(ncm.lfMessageFont.lfItalic); // Italic
					tmp.Write<BYTE>(ncm.lfMessageFont.lfCharSet); // CharSet
					tmp.WriteString(ncm.lfMessageFont.lfFaceName);

					// Then come the two controls.  First is the static text.
					tmp.AlignToDword();
					tmp.Write<DWORD>(0); // help id
					tmp.Write<DWORD>(0); // window extended style
					tmp.Write<DWORD>(WS_CHILD | WS_VISIBLE); // style
					tmp.Write<WORD>(7); // x
					tmp.Write<WORD>(7); // y
					tmp.Write<WORD>(200 - 14); // width
					tmp.Write<WORD>(80 - 7 - 14 - 7); // height
					tmp.Write<DWORD>(-1); // control ID
					tmp.Write<DWORD>(0x0082FFFF); // static
					tmp.WriteString(pszMessage); // text
					tmp.Write<WORD>(0); // no extra data

					// Second control is the OK button.
					tmp.AlignToDword();
					tmp.Write<DWORD>(0); // help id
					tmp.Write<DWORD>(0); // window extended style
					tmp.Write<DWORD>(WS_CHILD | WS_VISIBLE |
									 WS_GROUP | WS_TABSTOP | BS_DEFPUSHBUTTON); // style
					tmp.Write<WORD>(75); // x
					tmp.Write<WORD>(80 - 7 - 14); // y
					tmp.Write<WORD>(50); // width
					tmp.Write<WORD>(14); // height
					tmp.Write<DWORD>(IDCANCEL); // control ID
					tmp.Write<DWORD>(0x0080FFFF); // static
					tmp.WriteString(L"OK"); // text
					tmp.Write<WORD>(0); // no extra data

					// Template is ready - go display it.
					HINSTANCE hInst = GetModuleHandle(NULL);
					fSuccess = DialogBoxIndirect(hInst, tmp.Template(),
												 0, DlgProc) >= 0;
				}
				ReleaseDC(NULL, hdc); // fixed 11 May
			}
			return fSuccess;
		}
	} // namespace anonymous

	int Example3()
	{
		return FakeMessageBox();
	}
	// ***************************************************************//

	// ***********************Example4********************************//
	namespace
	{
#define IDI_ICON      101

#define IDB_WNDBUTTON 1000

#define IDB_DLGBUTTON 1001
		const char ClassName[] = "MainWindowClass";

		const char DialogClassName[] = "DialogClass";

		HWND hWndDlgBox;

		HWND hDlgButton;

		HWND hWndButton;



		LRESULT CALLBACK DlgProc3(HWND   hWndDlg,

								 UINT   Msg,

								 WPARAM wParam,

								 LPARAM lParam)

		{

			switch (Msg)

			{

				case WM_CREATE:

				{

					hDlgButton = CreateWindowEx(

						0,

						L"BUTTON",

						L"Close",

						WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,

						10,

						10,

						100,

						20,

						hWndDlg,

						(HMENU)IDB_DLGBUTTON,

						(HINSTANCE)GetWindowLong(hWndDlg, GWL_HINSTANCE),

						NULL);



					if (!hDlgButton)

						MessageBox(NULL, L"Dialog Button Failed.", L"Error", MB_OK | MB_ICONERROR);



					return TRUE;

				}

				break;



				case WM_COMMAND:

				{

					switch (LOWORD(wParam))

					{

						case IDB_DLGBUTTON:

						{

							switch (HIWORD(wParam))

							{

								case BN_CLICKED:

									SendMessage(hWndDlg, WM_CLOSE, 0, 0);

									break;

							}

						}

						break;

					}

					return 0;

				}

				break;



				case WM_CLOSE:

					DestroyWindow(hWndDlg);

					hWndDlgBox = NULL;

					break;



				default:

					return (DefWindowProc(hWndDlg, Msg, wParam, lParam));

			}

		}



		LRESULT CALLBACK WndProc(HWND    hWnd,

								 UINT    Msg,

								 WPARAM  wParam,

								 LPARAM  lParam)

		{
			USES_CONVERSION;
			switch (Msg)

			{

				case WM_CREATE:

				{

					WNDCLASSEX  wc;

					wc.cbSize = sizeof(WNDCLASSEX);

					wc.style = 0;

					wc.lpfnWndProc = (WNDPROC)DlgProc3;

					wc.cbClsExtra = 0;

					wc.cbWndExtra = 0;

					wc.hInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

					wc.hIcon = NULL;

					wc.hIconSm = NULL;

					wc.hCursor = LoadCursor(NULL, IDC_ARROW);

					wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

					wc.lpszMenuName = NULL;

					wc.lpszClassName = A2CW(DialogClassName);



					if (!RegisterClassEx(&wc))

					{

						MessageBox(NULL, L"Failed To Register The Dialog Class.", L"Error", MB_OK | MB_ICONERROR);

						return FALSE;

					}



					hWndButton = CreateWindowEx(

						0,

						L"BUTTON",

						L"Open Dialog",

						WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,

						10,

						10,

						100,

						30,

						hWnd,

						(HMENU)IDB_WNDBUTTON,

						(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),

						NULL);



					if (!hWndButton)

						MessageBox(NULL, L"Main Window Button Failed.", L"Error", MB_OK | MB_ICONERROR);

				}

				break;



				case WM_COMMAND:

				{

					switch (LOWORD(wParam))

					{

						case IDB_WNDBUTTON:

						{

							switch (HIWORD(wParam))

							{

								case BN_CLICKED:

								{

									if (!hWndDlgBox)

									{

										hWndDlgBox = CreateWindowEx(

											WS_EX_DLGMODALFRAME | WS_EX_TOPMOST,

											A2CW(DialogClassName),

											L"Dialog Box",

											WS_VISIBLE | WS_POPUP | WS_CAPTION,

											100,

											100,

											200,

											100,

											hWnd,

											NULL,

											(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),

											NULL);



										if (!hWndDlgBox)

											MessageBox(NULL, L"Dialog Box Failed.", L"Error", MB_OK | MB_ICONERROR);

									}

								}

								break;

							}

						}

						break;

					}

					return 0;

				}

				break;



				case WM_CLOSE:

					DestroyWindow(hWnd);

					break;



				case WM_DESTROY:

					PostQuitMessage(0);

					break;



				default:

					return (DefWindowProc(hWnd, Msg, wParam, lParam));

			}



			return 0;

		}



		INT  Example4_Imp()

		{


			USES_CONVERSION;
			HINSTANCE  hInstance = GetModuleHandle(NULL);
			WNDCLASSEX    wc;



			wc.cbSize = sizeof(WNDCLASSEX);

			wc.style = 0;

			wc.lpfnWndProc = (WNDPROC)WndProc;

			wc.cbClsExtra = 0;

			wc.cbWndExtra = 0;

			wc.hInstance = hInstance;

			wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));

			wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));

			wc.hCursor = LoadCursor(NULL, IDC_ARROW);

			wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

			wc.lpszMenuName = NULL;

			wc.lpszClassName = A2CW(ClassName);



			if (!RegisterClassEx(&wc))

			{

				MessageBox(NULL, L"Failed To Register The Window Class.", L"Error", MB_OK | MB_ICONERROR);

				return 0;

			}



			HWND    hWnd;



			hWnd = CreateWindowEx(

				WS_EX_CLIENTEDGE,

				A2CW(ClassName),

				L"Modeless Dialog Boxes",

				WS_OVERLAPPEDWINDOW,

				CW_USEDEFAULT,

				CW_USEDEFAULT,

				240,

				120,

				NULL,

				NULL,

				hInstance,

				NULL);

			if (!hWnd)
			{
				MessageBox(NULL, L"Window Creation Failed.", L"Error", MB_OK | MB_ICONERROR);
				return 0;
			}

			ShowWindow(hWnd, SW_SHOW);
			UpdateWindow(hWnd);

			MSG    Msg;

			while (GetMessage(&Msg, NULL, 0, 0))
			{
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
			return Msg.wParam;

		}

	} // namespace anonymous

	int Example4()
	{
		return Example4_Imp();
	}
	// ***************************************************************//

	// ***********************Example5********************************//
	namespace
	{
		LRESULT CALLBACK WndProc5(HWND, UINT, WPARAM, LPARAM);
		LRESULT CALLBACK DialogProc5(HWND, UINT, WPARAM, LPARAM);

		void CreateDialogBox(HWND);
		void RegisterDialogClass(HWND);

		HINSTANCE ghInstance;

		HWND hwnd;

		int Example5_Imp(HINSTANCE hInstance)
		{

			MSG  msg;

			WNDCLASSW wc = { 0 };

			wc.lpszClassName = L"Window";
			wc.hInstance = hInstance;
			wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
			wc.lpfnWndProc = (WNDPROC)WndProc5;

			RegisterClassW(&wc);
			hwnd = CreateWindowW(wc.lpszClassName, L"Window",
								   WS_OVERLAPPEDWINDOW | WS_VISIBLE,
								 100, 100, 250, 150, NULL, NULL, hInstance, NULL);

			ghInstance = hInstance;

			while (GetMessage(&msg, NULL, 0, 0))
			{
				DispatchMessage(&msg);
			}

			long a;
			std::cout << "Input anything to continue.\n";
			std::cin >> a;

			return (int)msg.wParam;
		}

		LRESULT CALLBACK WndProc5(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{

			switch (msg)
			{

				case WM_CREATE:
					RegisterDialogClass(hwnd);
					CreateWindowW(L"button", L"Show dialog",
								  WS_VISIBLE | WS_CHILD,
								  20, 50, 95, 25, hwnd, (HMENU)1, NULL, NULL);
					break;

				case WM_COMMAND:
					CreateDialogBox(hwnd);
					break;

				case WM_DESTROY:
				{
					PostQuitMessage(0);
					return 0;
				}
			}
			return DefWindowProcW(hwnd, msg, wParam, lParam);
		}

		LRESULT CALLBACK DialogProc5(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
			switch (msg)
			{

				case WM_CREATE:
					CreateWindowW(L"button", L"Ok",
								  WS_VISIBLE | WS_CHILD,
								  50, 50, 80, 25, hwnd, (HMENU)1, NULL, NULL);
					break;

				case WM_COMMAND:
					DestroyWindow(hwnd);
					break;

				case WM_CLOSE:
					DestroyWindow(hwnd);
					break;

			}

			return (DefWindowProcW(hwnd, msg, wParam, lParam));
		}

		void RegisterDialogClass(HWND hwnd)
		{

			WNDCLASSEXW wc = { 0 };
			wc.cbSize = sizeof(WNDCLASSEXW);
			wc.lpfnWndProc = (WNDPROC)DialogProc5;
			wc.hInstance = ghInstance;
			wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
			wc.lpszClassName = L"DialogClass";
			RegisterClassExW(&wc);

		}

		void CreateDialogBox(HWND hwnd)
		{

			//CreateWindowExW(WS_EX_DLGMODALFRAME | WS_EX_TOPMOST, L"DialogClass", L"Dialog Box",
			//				WS_VISIBLE | WS_SYSMENU | WS_CAPTION, 100, 100, 200, 150,
			//				NULL, NULL, ghInstance, NULL);

			CreateWindowExW(WS_EX_DLGMODALFRAME | WS_EX_TOPMOST, L"DialogClass", L"Dialog Box",
							WS_VISIBLE | WS_SYSMENU | WS_CAPTION, 100, 100, 200, 150,
							NULL, NULL, ghInstance, NULL);

		}
	}

	int Example5()
	{
		HINSTANCE aInstance = GetModuleHandle(NULL);
		return Example5_Imp(aInstance);
	}

	// ***************************************************************//
	// ***********************Example6********************************//
	namespace
	{
		LRESULT CALLBACK WndProc6(HWND, UINT, WPARAM, LPARAM);
		LRESULT CALLBACK PanelProc6(HWND, UINT, WPARAM, LPARAM);

		void RegisterPanel(void);
		COLORREF ShowColorDialog(HWND);

		COLORREF gColor = RGB(255, 255, 255);

		int Example6_Imnp(HINSTANCE hInstance)
		{

			MSG  msg;
			WNDCLASSW wc = { 0 };
			wc.lpszClassName = L"Color dialog box";
			wc.hInstance = hInstance;
			wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
			wc.lpfnWndProc = WndProc6;

			RegisterClassW(&wc);
			CreateWindowW(wc.lpszClassName, L"Color dialog box",
						  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
						  150, 150, 250, 200, 0, 0, hInstance, 0);

			while (GetMessage(&msg, NULL, 0, 0))
			{
				DispatchMessage(&msg);
			}

			
				
			return (int)msg.wParam;
		}

		LRESULT CALLBACK WndProc6(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{

			static HWND hwndPanel;

			switch (msg)
			{

				case WM_CREATE:
				{
					CreateWindowW(L"button", L"Color",
								  WS_VISIBLE | WS_CHILD,
								  20, 30, 80, 25,
								  hwnd, (HMENU)1, NULL, NULL);

					RegisterPanel();
					hwndPanel = CreateWindowW(L"Panel", NULL,
											  WS_CHILD | WS_VISIBLE,
											  130, 30, 80, 80, hwnd, (HMENU)2, NULL, NULL);
					break;
				}

				case WM_COMMAND:
				{
					gColor = ShowColorDialog(hwnd);
					InvalidateRect(hwndPanel, NULL, TRUE);
					break;
				}

				case WM_DESTROY:
				{
					PostQuitMessage(0);
					break;
				}
			}

			return DefWindowProcW(hwnd, msg, wParam, lParam);
		}

		LRESULT CALLBACK PanelProc6(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{

			HDC hdc;
			PAINTSTRUCT ps;
			RECT rect;

			switch (msg)
			{

				case WM_PAINT:
				{
					GetClientRect(hwnd, &rect);
					hdc = BeginPaint(hwnd, &ps);
					SetBkColor(hdc, gColor);
					ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rect, L"", 0, NULL);
					EndPaint(hwnd, &ps);
					break;
				}
			}

			return DefWindowProc(hwnd, msg, wParam, lParam);
		}

		COLORREF ShowColorDialog(HWND hwnd)
		{

			CHOOSECOLOR cc;
			static COLORREF crCustClr[16];

			ZeroMemory(&cc, sizeof(cc));
			cc.lStructSize = sizeof(cc);
			cc.hwndOwner = hwnd;
			cc.lpCustColors = (LPDWORD)crCustClr;
			cc.rgbResult = RGB(0, 255, 0);
			cc.Flags = CC_FULLOPEN | CC_RGBINIT;
			ChooseColor(&cc);

			return cc.rgbResult;
		}

		void RegisterPanel(void)
		{

			WNDCLASSW rwc = { 0 };
			rwc.lpszClassName = L"Panel";
			rwc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
			rwc.lpfnWndProc = PanelProc6;
			RegisterClassW(&rwc);
		}

	} // namespace anonymous 
	int Example6()
	{
		HINSTANCE hInstance = GetModuleHandle(NULL);
		return Example6_Imnp(hInstance);
	}
	// ***************************************************************//
}
