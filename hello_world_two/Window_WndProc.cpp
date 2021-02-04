#include "Window.h"

LRESULT CWindow::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	CWindow* wnd = nullptr;
	
	if(uMsg == WM_CREATE) {
		wnd = reinterpret_cast<CWindow*>(reinterpret_cast<LPCREATESTRUCTW>(lParam)->lpCreateParams);
		SetWindowLongPtrW(hWnd, GWL_USERDATA, reinterpret_cast<LONG_PTR>(wnd));
		wnd->OnCreate(lParam);
	} else {
		wnd = reinterpret_cast<CWindow*>(GetWindowLongPtrW(hWnd, GWL_USERDATA));
	}
	
	return wnd->WindowProc_internal(hWnd, uMsg, wParam, lParam);
}

LRESULT CWindow::WindowProc_internal(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch(uMsg) {
		case WM_KEYDOWN:
			this->OnKeyDown(wParam);
			break;
		case WM_CLOSE:
			this->OnClose();
			break;
		case WM_COMMAND:
			this->OnCommand(wParam);
			break;
		default:
			return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}
	
	return 0; // For compiler
}