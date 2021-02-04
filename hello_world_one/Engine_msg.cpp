#include "Engine.h"

// For lab's
#define VK_T 0x54
extern void __cdecl Lab(void);

void CEngine::Run() {
	MSG msg;
	
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	SetForegroundWindow(m_hWnd);
	
	memset(&msg, 0, sizeof(MSG));
	while(msg.message != WM_QUIT) {
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else Render();
	}
}

LRESULT CALLBACK CEngine::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	CEngine* engine = NULL;
	
	if(uMsg == WM_CREATE) {
		engine = reinterpret_cast<CEngine*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
		SetWindowLongPtr(hWnd, GWL_USERDATA, reinterpret_cast<LONG_PTR>(engine));
	} else {
		engine = reinterpret_cast<CEngine*>(GetWindowLongPtr(hWnd, GWL_USERDATA));
	}
	
	return engine->WndProc_Intl(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK CEngine::WndProc_Intl(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch(uMsg) {
		case WM_CLOSE:
			DestroyWindow(hWnd);
			UnregisterClass(TEXT("C_KWND"), m_hInst);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			if(wParam == VK_S) SShot();
			if(wParam == VK_T) Lab();
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	
	return 0;
}