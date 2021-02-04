#include "RenderDevice.h"

CRenderDevice::CRenderDevice() {
	m_pD3D = nullptr;
	m_pD3Dev = nullptr;
	m_hRenderWnd = nullptr;
	
	memset(&m_d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));
}

void CRenderDevice::Init() {
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	R_ASSERT(m_pD3D);
	
	D3DADAPTER_IDENTIFIER9 adapter;
	m_pD3D->GetAdapterIdentifier(0, 0, &adapter);
	Msg("* RENDER DEVICE:");
	Msg("- ID:\t%s", adapter.DeviceName);
	Msg("- DESC:\t%s", adapter.Description);
	Msg("- DRV:\t%s", adapter.Driver);
	
	int nProduct = HIWORD(adapter.DriverVersion.HighPart), 
		nVersion = LOWORD(adapter.DriverVersion.HighPart), 
		nSubVersion = HIWORD(adapter.DriverVersion.LowPart), 
		nBuild = LOWORD(adapter.DriverVersion.LowPart);
	Msg("- DRV VER:\t%d.%d.%d.%d", nProduct, nVersion, nSubVersion, nBuild);
}

void CRenderDevice::Destroy() {
	if(m_pD3Dev) {
		m_pD3Dev->Release();
		m_pD3Dev = nullptr;
	}
	
	if(m_pD3D) {
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
	
	m_hRenderWnd = nullptr;
}

// Only windowed mode !
void CRenderDevice::CreateDevice(HWND hWnd) {
	if(!IsWindow(hWnd))
		FATAL("Incorrect window!");
	
	m_hRenderWnd = hWnd;
	
	/** Oh, Lil 
		This experiment failure because
		as a result Direct3D draw over menu & title bar :-) 
	**/
	RECT rcCLA;
	GetClientRect(m_hRenderWnd, &rcCLA);
	
	m_d3dpp.BackBufferWidth = rcCLA.right;
	m_d3dpp.BackBufferHeight = rcCLA.bottom;
	m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8; // Without Alpha-channel
	m_d3dpp.BackBufferCount = 1;
	m_d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	m_d3dpp.hDeviceWindow = m_hRenderWnd;
	m_d3dpp.Windowed = TRUE;
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	
	R_CHK(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hRenderWnd, 
							   D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_d3dpp, &m_pD3Dev));
							   
	Msg("* [D3D]: Device create successful!");
}

void CRenderDevice::Render() {
	m_pD3Dev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(130, 130, 130), 1.f, 0);
	
	m_pD3Dev->BeginScene();
	m_pD3Dev->EndScene();
	
	m_pD3Dev->Present(NULL, NULL, NULL, NULL);
}