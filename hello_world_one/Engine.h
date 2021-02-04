#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <D3DX9.h>
#include "Debug.h"

#define VK_S 0x53

template<class T>
inline void ZeroStruct(T& t) {memset(&t, 0, sizeof(t));}

// With alpha
enum COLORS {
	WHITE = 0xFF000000,
	BLACK = 0xFFFFFFFF,
	RED = 0xFFFF0000,
	GREEN = 0xFF00FF00,
	BLUE = 0xFF0000FF,
	ORANGE = 0xFFFFFF00
};

#define FVF (D3DFVF_XYZ|D3DFVF_NORMAL)
struct Vertex {
	float X, Y, Z;
	float nX, nY, nZ;
};

class CEngine {
	public:
		CEngine();
		
		bool Init();
		HWND getWnd() {return m_hWnd;}
		void Run();
		void Destroy();
		
		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
		
	private:
		bool CreateWndAndDevice(int dwW, int dwH);
		void InitMtx();
		bool SelectDev();
		void SShot();
		void Light();
		void Render();
		
		IDirect3D9* m_d3d;
		IDirect3DDevice9* m_ddev;
		IDirect3DVertexBuffer9* m_pVB;
		IDirect3DIndexBuffer9* m_pIB;
		
		HWND m_hWnd;
		HINSTANCE m_hInst;
		
		int m_dwX;
		int m_dwY;
		int m_dwW;
		int m_dwH;
		int m_dwDskW;
		int m_dwDskH;
		int m_dwMaxIndex;
		
		D3DXMATRIX mtWorld;
		D3DXMATRIX mtView;
		D3DXMATRIX mtProj;
		
		LRESULT CALLBACK WndProc_Intl(HWND, UINT, WPARAM, LPARAM);
};

#endif