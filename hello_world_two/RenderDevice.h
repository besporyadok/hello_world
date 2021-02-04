#ifndef __RENDERDEVICE_H__
#define __RENDERDEVICE_H__

#include <d3dx9.h>

#include "xray/xray.h"

class CRenderDevice {
	public:
		CRenderDevice();
		
		void Init();
		void CreateDevice(HWND hWnd);
		void Render();
		void Destroy();
		
	private:
		IDirect3D9* m_pD3D;
		IDirect3DDevice9* m_pD3Dev;
		
		D3DPRESENT_PARAMETERS m_d3dpp;
		HWND m_hRenderWnd;
};

#endif