#include "Engine.h"

#define IDX_CNT 18
#define IDX_BUF_SIZE (IDX_CNT*sizeof(short))
short const Indexes[IDX_CNT] = {
	// Front side
	0, 1, 2,
	3, 0, 2,
	// Right side
	4, 3, 2,
	5, 4, 2,
	// Top side
	6, 2, 1,
	5, 2, 6
};

#define VERT_CNT 7
Vertex const Vertices[VERT_CNT] = {
	{-5.f, -5.f, 0.f, 0.f, 0.f, -1.f}, // 0
	{-5.f, 5.f, 0.f, 0.f, 0.f, -1.f}, // 1
	{5.f, 5.f, 0.f, 0.f, 0.f, -1.f}, // 2
	{5.f, -5.f, 0.f, 0.f, 0.f, -1.f}, // 3
	{10.f, -5.f, 5.f, 1.f, 0.f, 0.f}, // 4
	{10.f, 5.f, 5.f, 1.f, 0.f, 0.f}, // 5
	{0.f, 5.f, 5.f, 0.f, 1.f, 0.f} // 6
};

CEngine::CEngine() : m_dwX(0), m_dwY(0), 
					 m_dwW(300), m_dwH(300),
					 m_dwMaxIndex(0) {
	m_hInst = GetModuleHandle(NULL);
	m_dwDskW = GetSystemMetrics(SM_CXSCREEN);
	m_dwDskH = GetSystemMetrics(SM_CYSCREEN);
	
	m_hWnd = NULL;
	m_d3d = NULL;
	m_ddev = NULL;
	m_pVB = NULL;
	m_pIB = NULL;
}

bool CEngine::Init() {
	D3DVERTEXBUFFER_DESC vbDesc;
	D3DINDEXBUFFER_DESC ibDesc;
	VOID* pTmp = NULL;
	
	Dbg.Init(TEXT("Dbg.log"));
	
	if(!CreateWndAndDevice(800, 600)) {
		Dbg.Msg(TEXT("Can't create wnd & dev!\n"));
		return false;
	}
	
	DXASSERT(m_ddev->CreateVertexBuffer(VERT_CNT*sizeof(Vertex), D3DUSAGE_WRITEONLY, FVF, D3DPOOL_DEFAULT, &m_pVB, NULL));
	
	m_pVB->GetDesc(&vbDesc);
	Dbg.MsgEx(TEXT("VB buffer create. Size: %d(bytes).\n"), vbDesc.Size);
	
	if(!(IDX_CNT > m_dwMaxIndex)) {
		DXASSERT(m_ddev->CreateIndexBuffer(IDX_BUF_SIZE, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT,
				 &m_pIB, NULL));
				 
		m_pIB->GetDesc(&ibDesc);
		Dbg.MsgEx(TEXT("IB buffer create. Size: %d(bytes).\n"), ibDesc.Size);

		m_pIB->Lock(0, IDX_BUF_SIZE, &pTmp, 0);
			memcpy_s(pTmp, IDX_BUF_SIZE, Indexes, IDX_BUF_SIZE);
		m_pIB->Unlock();
		
		pTmp = NULL;
	}
	
	m_pVB->Lock(0, sizeof(Vertices), &pTmp, 0);
		memcpy_s(pTmp, sizeof(Vertices), Vertices, sizeof(Vertices));
	m_pVB->Unlock();
		
	InitMtx();
	
	return true;
}

void CEngine::Destroy() {
	if(m_pIB) {
		m_pIB->Release();
		m_pIB = NULL;
	}
	
	if(m_pVB) {
		m_pVB->Release();
		m_pVB = NULL;
	}
	
	m_ddev->Release();
	m_d3d->Release();
	
	m_ddev = NULL;
	m_d3d = NULL;
	
	Dbg.Destroy();
}

bool CEngine::CreateWndAndDevice(int dwW, int dwH) {
	WNDCLASSEX wc;
	D3DPRESENT_PARAMETERS d3dpp;
	
	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.hInstance = m_hInst;
	wc.lpszClassName = TEXT("C_KWND");
	
	if(!RegisterClassEx(&wc)) {
		MessageBoxEx(NULL, TEXT("Can't initialize wnd cls!"), TEXT("Critical error!"), MB_ICONHAND, 0);
		return false;
	}
	
	m_dwW = dwW; m_dwH = dwH;
	
	m_dwX = (m_dwDskW >> 2) + (300 >> 2);
	m_dwY = (m_dwDskH >> 2) + (300 >> 2);
	
	m_hWnd = CreateWindowEx(0, TEXT("C_KWND"), TEXT("HelloWorld"), WS_OVERLAPPED | WS_SYSMENU, 
						  m_dwX, m_dwY, m_dwW, m_dwH, NULL, NULL, m_hInst, this);
	if(!m_hWnd) {
		MessageBoxEx(NULL, TEXT("Can't create wnd!"), TEXT("Critical error!"), MB_ICONHAND, 0);
		return false;
	}
	
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if(!m_d3d) {
		MessageBoxEx(NULL, TEXT("Can't get D3D!"), TEXT("Critical error!"), MB_ICONHAND, 0);
		return false;
	}
	
	if(!SelectDev())
		return false;
	
	memset(&d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.BackBufferWidth = m_dwW;
	d3dpp.BackBufferHeight = m_dwH;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = m_hWnd;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = 0;
		
	DXASSERT(m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, 
					D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_ddev));
	
	m_ddev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	
	Light();
	
	return true;
}

void CEngine::Render() {	
	m_ddev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 0), 1.f, 0);
	
	m_ddev->BeginScene();
		m_ddev->SetFVF(FVF);
		m_ddev->SetStreamSource(0, m_pVB, 0, sizeof(Vertex));
		m_ddev->SetIndices(m_pIB);
		m_ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, VERT_CNT, 0, 6);
	m_ddev->EndScene();
	
	m_ddev->Present(NULL, NULL, NULL, NULL);
}

bool CEngine::SelectDev() {
	D3DADAPTER_IDENTIFIER9 devID;
	D3DCAPS9 caps;
	
	Dbg.MsgEx(TEXT("Adapter\'s in sys: %d\n"), m_d3d->GetAdapterCount());
	
	m_d3d->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &devID);
	Dbg.Msg(TEXT("Primary adapter info:\n"));
	Dbg.MsgEx(TEXT("\tName: %s\n"), devID.DeviceName);
	Dbg.MsgEx(TEXT("\tDriver: %s\n"), devID.Driver);
	Dbg.MsgEx(TEXT("\tDriver version: %d.%d\n"), LOWORD(devID.DriverVersion.HighPart), HIWORD(devID.DriverVersion.LowPart));
	
	// Add a support check in HAL & BBuffer format a good way :-) 
	m_d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		Dbg.Msg(TEXT("\tT&L: yes!\n"));
		
		m_dwMaxIndex = caps.MaxVertexIndex;
		return true;
	}
	
	return false;
}

void CEngine::SShot() {
	IDirect3DSurface9* pSurf = NULL;
	
	m_ddev->CreateOffscreenPlainSurface(m_dwDskW, m_dwDskH, D3DFMT_A8R8G8B8, D3DPOOL_SCRATCH, &pSurf, NULL);
	DXASSERT(m_ddev->GetFrontBufferData(0, pSurf)); // Hard chk?
	
	D3DXSaveSurfaceToFile(TEXT("Sshot.jpg"), D3DXIFF_JPG, pSurf, NULL, NULL);
	
	if(pSurf) pSurf->Release();
}

void CEngine::InitMtx() {
	D3DXMATRIX mt;
	
	D3DXMatrixIdentity(&mtWorld);
	D3DXMatrixScaling(&mt, 2.f, 2.f, 2.f);
	D3DXMatrixMultiply(&mtWorld, &mtWorld, &mt);
	m_ddev->SetTransform(D3DTS_WORLD, &mtWorld);
	
	D3DXVECTOR3 pos(3.f, 15.f, -20.f);
	D3DXVECTOR3 look(0.f, 0.f, 0.f);
	D3DXVECTOR3 up(0.f, 1.f, 0.f);
	D3DXMatrixLookAtLH(&mtView, &pos, &look, &up);
	m_ddev->SetTransform(D3DTS_VIEW, &mtView);
	
	D3DXMatrixPerspectiveFovLH(&mtProj, D3DX_PI*0.5f, (float)m_dwDskW/(float)m_dwDskH, 1.f, 100.f);
	m_ddev->SetTransform(D3DTS_PROJECTION, &mtProj);
	
	D3DVIEWPORT9 vp = {0, 0, m_dwW, m_dwH, 0, 1};
	m_ddev->SetViewport(&vp);
}

void CEngine::Light() {
	D3DLIGHT9 light;
	D3DMATERIAL9 mtl;
	D3DCOLORVALUE color;
	D3DXVECTOR3 vec;
	
//	m_ddev->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_ddev->SetRenderState(D3DRS_SPECULARENABLE, FALSE);

	color.r = 0.5f;
	color.g = 0.5f;
	color.b = 1.f;
	color.a = 0.f;
	
	ZeroStruct(mtl);
	mtl.Ambient = mtl.Diffuse = color;
	m_ddev->SetMaterial(&mtl);
	
	m_ddev->SetRenderState(D3DRS_AMBIENT, ORANGE);
	
	ZeroStruct(light);
	light.Type = D3DLIGHT_SPOT;
	
	color.r = 1.f;
	color.g = 0.f;
	color.b = 1.f;
	color.a = 0.f;
	light.Diffuse = color;
	
	vec = D3DXVECTOR3(0.f, 1.f, -20.f);
	light.Position = vec;
	vec = D3DXVECTOR3(0.f, 0.f, 1.f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vec);
	
	light.Range = 25.f;
	light.Phi = 1.f;
	m_ddev->SetLight(0, &light);
	m_ddev->LightEnable(0, TRUE);
}