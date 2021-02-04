#include "Window.h"

bool CWindow::m_bIsMainWindowCreate = false;

CWindow::CWindow(HINSTANCE hInst) {
	m_hInst = hInst;
	m_bIsMainWindowCreate = false;
	m_hMainWindow = nullptr;
	
	InitWindowClasses();
}

void CWindow::InitWindowClasses() {
	m_szWindowClasses[WINDOWTYPE_MAIN] = L"C_KMWND";
	m_szWindowClasses[WINDOWTYPE_RENDER] = L"C_KRWND";
}

void CWindow::RegisterWindowClass(EWindowType winType) {
	WNDCLASSEXW wc;
	memset(&wc, 0, sizeof(WNDCLASSEXW));
	
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.hInstance = m_hInst;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_szWindowClasses[winType];
	
	RegisterClassExW(&wc);
}

HWND CWindow::CreateMainWindow(int nWidth, int nHeight) {
	if(m_bIsMainWindowCreate) {
		return nullptr;
	}
	
	RegisterWindowClass(WINDOWTYPE_MAIN);
	
	HWND hWndDesktop = GetDesktopWindow();
	
	RECT rcDesktop;
	GetWindowRect(hWndDesktop, &rcDesktop);
	
	int X = (rcDesktop.right - rcDesktop.left)/2 - (nWidth - 200);
	int Y = (rcDesktop.bottom - rcDesktop.top)/2 - (nHeight - 200);
	
	m_hMainWindow = CreateWindowExW(0, m_szWindowClasses[WINDOWTYPE_MAIN], L"CW", WS_OVERLAPPED | WS_SYSMENU, 
									X, Y, nWidth, nHeight, hWndDesktop, NULL, m_hInst, this);
	if(IsWindow(m_hMainWindow))
		m_bIsMainWindowCreate = true;
	
	return m_hMainWindow;
}

HWND CWindow::CreateChildWindow(EWindowType winType, int nWidth, int nHeight) {
	if(!m_bIsMainWindowCreate) {
		SetLastErrorEx(ERROR_INVALID_HANDLE, 0);		
		return nullptr;
	}
	
	HWND hWnd = CreateWindowExW(0, m_szWindowClasses[winType], m_szWindowClasses[winType], WS_CHILD,
							   CW_USEDEFAULT, CW_USEDEFAULT, nWidth, nHeight, m_hMainWindow, NULL, m_hInst, NULL);
	
	return hWnd;
}

void CWindow::DestroyMainWindow() {
	if(m_hMainWindow) {
		DestroyWindow(m_hMainWindow);
		UnregisterClassW(m_szWindowClasses[WINDOWTYPE_MAIN], m_hInst);
		m_hMainWindow = nullptr;
		m_bIsMainWindowCreate = false;
	}
}