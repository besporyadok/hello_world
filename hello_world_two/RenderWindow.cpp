#include "RenderWindow.h"

CRenderWindow::CRenderWindow() : super(GetModuleHandleW(NULL)) {
	m_hWnd = nullptr;
}

void CRenderWindow::Init() {
	FATAL("");
	
	m_hWnd = CreateChildWindow(WINDOWTYPE_RENDER, 320, 200);
	if(!IsWindow(m_hWnd))
		FATAL("Create render window failure!");
}

void CRenderWindow::Destroy() {
	if(IsWindow(m_hWnd)) {
		DestroyWindow(m_hWnd);
		m_hWnd = nullptr;
	}
}