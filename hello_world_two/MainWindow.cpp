#include "MainWindow.h"

CMainWindow::CMainWindow(HINSTANCE hInst) : super(hInst)
{
	m_hWnd = nullptr;
	m_hRenderWnd = nullptr;
	m_pMainMenu = nullptr;
	m_pRenderWnd = nullptr;
	m_cRef = 1;
}

void CMainWindow::Init() {
	m_hWnd = CreateMainWindow();
	
	m_pRenderWnd = new CRenderWindow();
	m_pRenderWnd->Init();
	
	m_hRenderWnd = m_pRenderWnd->get_Handle();
	
	m_pMainMenu = new CMainMenu();
	
	IUIFramework* pRib = nullptr;
	R_CHK(CoCreateInstance(CLSID_UIRibbonFramework, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pRib)));
	pRib->Initialize(m_hWnd, this);
	
	m_pMainMenu->Init(m_hWnd, pRib, false);
}

void CMainWindow::Destroy() {
	if(m_pMainMenu) {
		m_pMainMenu->Destroy();
		delete m_pMainMenu;
		m_pMainMenu = nullptr;
	}
	
	if(m_pRenderWnd) {
		m_pRenderWnd->Destroy();
		m_hRenderWnd = nullptr;
		
		delete m_pRenderWnd;
		m_pRenderWnd = nullptr;
	}
	
	DestroyMainWindow();
}

void CMainWindow::Show() {
	ShowWindow(m_hWnd, SW_SHOW);
	ShowWindow(m_hRenderWnd, SW_SHOW);
}

void CMainWindow::ShowAboutDialog() {	
	AboutDialog dlg;
	memset(&dlg, 0, sizeof(AboutDialog));
	
	dlg.style = WS_SYSMENU | WS_VISIBLE | DS_CENTER;
	dlg.cx = 50;
	dlg.cy = 100;
	dlg.cdit = 1;
	wcscpy_s(dlg.wszTitle, 6, L"About");
	
	ELB(dlg, text).style = WS_CHILD | WS_VISIBLE | SS_CENTER;
	ELB(dlg, text).id = 0x228;
	ELB(dlg, text).wSysClass = 0xFFFF; // System window class
	ELB(dlg, text).wIdClass = 0x0082;  // Static
	ELB(dlg, text).cx = dlg.cx;
	ELB(dlg, text).cy = dlg.cy;
	wcscpy_s(dlg.text.wszTitle, 1, L"");
	
	DialogBoxIndirectParamW(m_hInst, reinterpret_cast<LPCDLGTEMPLATEW>(&dlg), m_hWnd, AboutProc, 0);
}

void CMainWindow::OnCreate(LPARAM) {}

void CMainWindow::OnKeyDown(WPARAM wKey) {
	if(wKey == VK_ESCAPE)
		PostQuitMessage(0);
}

void CMainWindow::OnClose() {
	PostQuitMessage(0);
}

void CMainWindow::OnCommand(WPARAM wParam) {
	switch(LOWORD(wParam)) {
		case CMainMenu::MENU_FILE_EXIT:
			PostQuitMessage(0);
			break;
		case CMainMenu::MENU_ABOUT:
			ShowAboutDialog();
			break;
	}
}

// SUPPORT FOR RIBBON UI FRAMEWORK

// IUnknown
STDMETHODIMP CMainWindow::QueryInterface(REFIID iid, PVOID* ppv) {
	if(iid == __uuidof(IUnknown)) {
		*ppv = static_cast<IUnknown*>(this);
	} else if(iid == __uuidof(IUIApplication)) {
		*ppv = static_cast<IUIApplication*>(this);
	} else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	
	AddRef();
	return S_OK;
}

STDMETHODIMP_(ULONG) CMainWindow::AddRef() {
	return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) CMainWindow::Release() {
	LONG nRet = InterlockedDecrement(&m_cRef);
	
	if(nRet == 0) {
		delete this; // ! AUCHTUNG !
	}
	
	return nRet;
}

// IUIApplication
STDMETHODIMP CMainWindow::OnViewChanged(UINT32, UI_VIEWTYPE, IUnknown*, UI_VIEWVERB, INT32) {
	return E_NOTIMPL;
}

STDMETHODIMP CMainWindow::OnCreateUICommand(UINT32, UI_COMMANDTYPE, IUICommandHandler**) {
	return E_NOTIMPL;
}

STDMETHODIMP CMainWindow::OnDestroyUICommand(UINT32, UI_COMMANDTYPE, IUICommandHandler*) {
	return E_NOTIMPL;
}