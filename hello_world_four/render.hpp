#pragma once

#include <d3dx9.h>

#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")

#include "iinput.hpp"
#include "camera.hpp"
#include "r_types.h"

class CRender : public IInput {
	public:
		CRender();
		~CRender();
		
		inline HRESULT get_LastErr(void) const { return m_hLastErr; }
		
		bool Init(HWND hWnd, unsigned nWidth, unsigned nHeight);
		void Render();
		void Destroy();
		
		void SetMatrix(D3DXMATRIX* pView, D3DXMATRIX* pPrj);
		void SetStates();
		void InitLight();
		void CreateCub();
	
	public:
		void OnInput();
		void OnKeyDown(WPARAM key);
		
	private:
		CRender(const CRender&) {}
		CRender& operator=(const CRender&) {}
	
	private:
		IDirect3D9* m_pD3D;
		IDirect3DDevice9* m_pDev;
		IDirect3DVertexBuffer9* m_pVB;
		IDirect3DIndexBuffer9* m_pIB;
		IDirect3DTexture9* m_pText;
		
		IDirect3DSwapChain9* m_pSC;
		D3DPRESENT_PARAMETERS* m_pDPP;
		
		CCamera* m_pCam;
		
		HRESULT m_hLastErr;
};