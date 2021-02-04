#include "Global.h"

SGlobal gEnv;

SGlobal::SGlobal() {
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	
	Core._initialize("CW");
	
	pDev = new CRenderDevice();
	pDev->Init();
}

SGlobal::~SGlobal() {
	if(pDev) {
		pDev->Destroy();
		delete pDev;
		pDev = nullptr;
	}
	
	// TODO: problem (NTSTATUS: 0xC0*05)!
	// Because xrSyncronize not contains valid pointer
	// to critical section at moment shutdown app.
	
	Core._destroy();
	
	CoUninitialize();
}