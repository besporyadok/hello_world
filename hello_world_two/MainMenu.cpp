#include "MainMenu.h"

CMainMenu::CMainMenu() {
	m_hMenu = nullptr;
	m_hWnd = nullptr;
	m_pRibbon = nullptr;
}

void CMainMenu::Init(HWND hWnd, IUIFramework* pRib, bool bOldStyle) {
	m_hWnd = hWnd; m_bOldStyle = bOldStyle;
		
	if(pRib) {
		R_ASSERT(pRib);
		m_pRibbon = pRib;
	}
	
	(m_bOldStyle) ? CreateOldStyleMenu() : CreateNewStyleMenu();
}

void CMainMenu::Destroy() {
	if(m_pRibbon) {
		m_pRibbon->Release();
		m_pRibbon = nullptr;
	}
	
	if(m_bOldStyle && IsMenu(m_hMenu)) {
		DestroyMenu(m_hMenu);
		m_hMenu = nullptr;
		m_hWnd = nullptr;
	}
}

void CMainMenu::CreateOldStyleMenu() {
	m_hMenu = CreateMenu();
	
	HMENU hMenuPopup = CreatePopupMenu();
	AppendMenuW(hMenuPopup, MF_STRING, (UINT_PTR)MENU_FILE_OPEN, L"Open...");
	AppendMenuW(hMenuPopup, MF_STRING, (UINT_PTR)MENU_FILE_EXIT, L"Exit");
	AppendMenuW(m_hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hMenuPopup, L"&File");
	
	AppendMenuW(m_hMenu, MF_STRING, (UINT_PTR)MENU_ABOUT, L"About");
	
	SetMenu(m_hWnd, m_hMenu);
}

void CMainMenu::CreateNewStyleMenu() {
	m_pRibbon->LoadUI(GetModuleHandleW(NULL), L"APPLICATION_RIBBON");
}