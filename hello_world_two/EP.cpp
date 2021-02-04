#include "Application.h"

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
	CApplication* pApp = new CApplication();
	pApp->Init();
	
	int nRetCode = pApp->Run();
	
	pApp->Destroy();
	delete pApp;
	
	return nRetCode;
}