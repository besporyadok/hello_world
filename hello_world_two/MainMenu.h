#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "Global.h"

#include "UIRibbon.h"

class CMainMenu {
	public:
		CMainMenu();
		
		void Init(HWND hWnd, IUIFramework* pRib = nullptr, bool bOldStyle = true);
		void CreateOldStyleMenu();
		void CreateNewStyleMenu();
		void Destroy();
		
		enum EMenuItem {
			MENU_FILE = 0x10,
			MENU_FILE_OPEN = 0x11,
			MENU_FILE_EXIT = 0x12,
			MENU_ABOUT = 0x20,
			MENU_END = 0xFF
		};
		
	private:
		bool m_bOldStyle;
	
		HWND m_hWnd;
		HMENU m_hMenu;
		
		IUIFramework* m_pRibbon;
};

#endif