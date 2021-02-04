#include "Engine.h"

INT WINAPI wWinMain(HINSTANCE, HINSTANCE, LPTSTR, INT) {
	CEngine* engine = new CEngine();
	if(!engine->Init()) {
		return -1;
	}
	
	engine->Run();
	
	engine->Destroy();
	delete engine;
	
	return 0;
}