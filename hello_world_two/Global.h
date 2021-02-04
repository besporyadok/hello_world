#ifndef __GLOBAL_H__
#define __GLOBAL_H__

// WinAPI headers
#include <Windows.h>

// X-Ray
#include "xray/xray.h"

// Other
#include "RenderDevice.h"

struct SGlobal {
		SGlobal();
		~SGlobal();
	
		CRenderDevice* pDev;
	
	private:
		SGlobal(SGlobal const&) {}
		SGlobal& operator=(SGlobal const&) {}
};

extern SGlobal gEnv;

#endif