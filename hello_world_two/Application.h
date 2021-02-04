#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Global.h"

#include "MainWindow.h"

class CApplication {
	public:
		CApplication();
		
		void Init();
		int Run();
		void Destroy();
		
	private:
		HINSTANCE m_hInst;
	
		CMainWindow* m_pMainWindow;
		HWND m_hMainWindow;
};

#endif