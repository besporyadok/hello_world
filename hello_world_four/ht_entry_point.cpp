#include <StdIO.h>
#include <WChar.h>
#include <memory>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "render.hpp"
#include "input.hpp"

#define DBG_BREAK __debugbreak()

void FatalErr(LPCWSTR lpszMsg, ...) {
	va_list arg = nullptr;
	WCHAR* pBuf = nullptr;
	
	va_start(arg, lpszMsg);
	{
		int nLen = _vscwprintf_l(lpszMsg, 0, arg);
		
		pBuf = new WCHAR[nLen * sizeof(WCHAR)];
		if(pBuf) {
			_vswprintf_l(pBuf, nLen, lpszMsg, 0, arg);
		}
	}
	va_end(arg);
	
	MessageBoxExW(nullptr, pBuf, L"Fatal Error", MB_ICONHAND, 0);
	
	if(pBuf) {
		delete[] pBuf;
		pBuf = nullptr;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch(uMsg) {
		case WM_CLOSE:
		case WM_QUIT:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			SInputParams ip;
			ip.action = IA_KEYDOWN;
			ip.wParam = wParam;
			ip.lParam = lParam;
		
			g_pInput->Notify(&ip);
			break;
		default:
			return DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}
	
	return 0; // For compiler
} 

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int) {
	WNDCLASSEXW wc;
	memset(&wc, 0, sizeof(wc));
	
	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandleW(nullptr);
	wc.hIcon = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = L"C_KWND";
	
	RegisterClassExW(&wc);
	
	DWORD dwStyle = WS_OVERLAPPED | WS_SYSMENU;
	RECT rc = {0, 0, 800, 600};
	AdjustWindowRectEx(&rc, dwStyle, FALSE, 0);
	
	unsigned nWidth = rc.right - rc.left;
	unsigned nHeight = rc.bottom - rc.top;
	
	POINT pos;
	pos.x = (GetSystemMetrics(SM_CXSCREEN) - nWidth) >> 2;
	pos.y = (GetSystemMetrics(SM_CYSCREEN) - nHeight) >> 2;
	
	HWND hWnd = CreateWindowExW(0, wc.lpszClassName, L"ht", dwStyle, pos.x, pos.y, nWidth, nHeight, 
								GetDesktopWindow(), nullptr, wc.hInstance, nullptr);
	if(!IsWindow(hWnd)) {
		FatalErr(L"Cannot create main window!\n\n0x%X", GetLastError());
		return -1;
	}
	
	g_pInput = new CInputListener();
	
	std::unique_ptr<CRender> render(new CRender());
	if(!render->Init(hWnd, nWidth, nHeight)) {
		FatalErr(L"Cannot init render!\n\n0x%X", render->get_LastErr());
		
		DestroyWindow(hWnd);
		hWnd = nullptr;
		
		return -1;
	}
	
	g_pInput->Register(render.get());
	
	render->CreateCub();
	
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	
	ShowWindow(hWnd, SW_SHOW);	
	do {
		if(PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		} else {
			render->Render();
		}
	} while(msg.message != WM_QUIT);
	
	render->Destroy();
	
	delete g_pInput;
	g_pInput = nullptr;
	
	return msg.wParam; 
}