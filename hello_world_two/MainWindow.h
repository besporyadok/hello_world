#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include "Window.h"
#include "MainMenu.h"
#include "RenderWindow.h"

class CMainWindow : public IUIApplication, public CWindow {
	private:
		typedef CWindow super;

	public:
		CMainWindow(HINSTANCE hInst);
		
		inline HWND get_Handle() const { return m_hWnd; }
		inline HWND get_RenderWnd() const { return m_hRenderWnd; }
		
		void Init();
		void Show();
		void Destroy();
		
		#include "MainWindow_About.h" // Oh, lil
		void ShowAboutDialog();
		static INT_PTR CALLBACK AboutProc(HWND, UINT, WPARAM, LPARAM);
		
		void OnCreate(LPARAM);
		void OnKeyDown(WPARAM);
		void OnClose();
		void OnCommand(WPARAM);
		
	private:
		STDMETHOD(QueryInterface(REFIID iid, PVOID*));
		STDMETHOD_(ULONG, AddRef());
		STDMETHOD_(ULONG, Release());
		
		STDMETHOD(OnCreateUICommand(UINT32, UI_COMMANDTYPE, IUICommandHandler**));
		STDMETHOD(OnViewChanged(UINT32, UI_VIEWTYPE, IUnknown*, UI_VIEWVERB, INT32));
		STDMETHOD(OnDestroyUICommand(UINT32, UI_COMMANDTYPE, IUICommandHandler*));
		
		LONG m_cRef;
		
	private:
		HWND m_hWnd;
		HWND m_hRenderWnd;
		
		CMainMenu* m_pMainMenu;
		CRenderWindow* m_pRenderWnd;
};

#endif