#ifndef __RENDERWINDOW_H__
#define __RENDERWINDOW_H__

#include "Window.h"

class CRenderWindow : public CWindow {
	private:
		typedef CWindow super;
	
	public:
		CRenderWindow();
		
		void Init();
		void Destroy();
		
		inline HWND get_Handle() const { return m_hWnd; }
		
	private:
		HWND m_hWnd;
	
		void OnCreate(LPARAM) { Msg("* [INF]: Render window create!"); }
		void OnKeyDown(WPARAM) {}
		void OnClose() {}
		void OnCommand(WPARAM) {}
};

#endif