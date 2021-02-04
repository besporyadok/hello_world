#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Global.h"

// This class & CMainWindow
// transform to monstrous mutants xD

// Singleton in future ? :-) 
class CWindow {
	public:
		CWindow(HINSTANCE hInst);
	
	protected:
		enum EWindowType {
			WINDOWTYPE_MAIN = 0,
			WINDOWTYPE_RENDER = 1,
			WINDOWTYPE_END
		};
	
		void RegisterWindowClass(EWindowType winType);
		HWND CreateMainWindow(int nWidth = 800, int Height = 600);
		HWND CreateChildWindow(EWindowType winType, int nWidth, int nHeight);
		void DestroyMainWindow();
		
		static bool m_bIsMainWindowCreate;
		HINSTANCE m_hInst;
		
		virtual void OnCreate(LPARAM) = 0;
		virtual void OnKeyDown(WPARAM) = 0;
		virtual void OnClose() = 0;
		virtual void OnCommand(WPARAM) = 0;
		
	private:
		HWND m_hMainWindow;
	
		const wchar_t* m_szWindowClasses[WINDOWTYPE_END+1];
		void InitWindowClasses();
	
		static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
		LRESULT CALLBACK WindowProc_internal(HWND, UINT, WPARAM, LPARAM);
};

#endif