#include "Application.h"

CApplication::CApplication() {
	m_hMainWindow = nullptr;
	m_pMainWindow = nullptr;
	m_hInst = GetModuleHandleW(NULL);
}

void CApplication::Init() {
	m_pMainWindow = new CMainWindow(m_hInst);
	m_pMainWindow->Init();
	
	m_hMainWindow = m_pMainWindow->get_Handle();
	gEnv.pDev->CreateDevice(m_pMainWindow->get_RenderWnd());
}

void CApplication::Destroy() {
	if(m_pMainWindow) {
		m_pMainWindow->Destroy();
		delete m_pMainWindow;
		m_pMainWindow = nullptr;
		m_hMainWindow = nullptr;
	}
}

int CApplication::Run() {
	m_pMainWindow->Show();
	
	MSG msg;
	memset(&msg, 0, sizeof(MSG));
	
	while(msg.message != WM_QUIT) {
		if(PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		} else {
			gEnv.pDev->Render();
		}
	}
	
	/* while(GetMessageW(&msg, NULL, 0, 0)) { -- old cycle
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	} */
	
	return msg.wParam;
}