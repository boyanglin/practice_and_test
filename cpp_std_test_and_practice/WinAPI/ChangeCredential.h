#ifndef CHANGE_CREDENTIAL_H_
#define CHANGE_CREDENTIAL_H_

#include <string>

#include <Windows.h>

namespace KBaseWin {


	class ChangeCredential {
	public:
		static const wchar_t* const CLASS_NAME;
		static const char* const ERR_MSG_TITLE;

		static const size_t WND_W = 340;
		static const size_t WND_H = 170;

		static const size_t BTN_OK_W = 150;
		static const size_t BTN_OK_H = 30;
		static const size_t BTN_OK_L = 10;
		static const size_t BTN_OK_T = 100;

		static const size_t BTN_CANCEL_W = 150;
		static const size_t BTN_CANCEL_H = 30;
		static const size_t BTN_CANCEL_L = 170;
		static const size_t BTN_CANCEL_T = 100;
		
		static const size_t STATIC_OLD_SECRET_W = 150;
		static const size_t STATIC_OLD_SECRET_H = 20;
		static const size_t STATIC_OLD_SECRET_L = 10;
		static const size_t STATIC_OLD_SECRET_T = 10;

		static const size_t STATIC_NEW_SECRET1_W = 150;
		static const size_t STATIC_NEW_SECRET1_H = 20;
		static const size_t STATIC_NEW_SECRET1_L = 10;
		static const size_t STATIC_NEW_SECRET1_T = 40;

		static const size_t STATIC_NEW_SECRET2_W = 150;
		static const size_t STATIC_NEW_SECRET2_H = 20;
		static const size_t STATIC_NEW_SECRET2_L = 10;
		static const size_t STATIC_NEW_SECRET2_T = 70;

		static const size_t EDIT_OLD_SECRET_W = 160;
		static const size_t EDIT_OLD_SECRET_H = 20;
		static const size_t EDIT_OLD_SECRET_L = 160;
		static const size_t EDIT_OLD_SECRET_T = 10;

		static const size_t EDIT_NEW_SECRET1_W = 160;
		static const size_t EDIT_NEW_SECRET1_H = 20;
		static const size_t EDIT_NEW_SECRET1_L = 160;
		static const size_t EDIT_NEW_SECRET1_T = 40;

		static const size_t EDIT_NEW_SECRET2_W = 160;
		static const size_t EDIT_NEW_SECRET2_H = 20;
		static const size_t EDIT_NEW_SECRET2_L = 160;
		static const size_t EDIT_NEW_SECRET2_T = 70;

		ChangeCredential(const std::string& credName);

		bool PopupWindow();

		std::string GetOldSecret()
		{
			return mOldSecret;
		}

		std::string GetNewSecret()
		{
			return mNewSecret;
		}

	private:
		std::string mOldSecret;
		std::string mNewSecret;

		HINSTANCE mHInstance;
		HWND mHWnd;
		WNDCLASSEX mWndClassEx;

		void createWNDCLASSEX();

		// add controls
		void addBtn_OK();
		void addBtn_Cancel();
		void addLabel_OldSecret();
		void addLabel_NewSecret1();
		void addLabel_NewSecret2();
		void addTextBox_Oldsecret();
		void addTextBox_NewSecret1();
		void addTextBox_NewSecret2();

	};
}


#endif