#include "render.hpp"
#include "timer.hpp"

#include "r_cube.h"

CRender::CRender() {
	m_hLastErr = E_FAIL;
	m_pD3D = nullptr;
	m_pDev = nullptr;
	m_pVB = nullptr;
	m_pIB = nullptr;
	m_pText = nullptr;
	
	m_pSC = nullptr;
	m_pDPP = nullptr;
	
	m_pCam = nullptr;
}

CRender::~CRender() {
//	Destroy();
}

bool CRender::Init(HWND hWnd, unsigned nWidth, unsigned nHeight) {
	if(!IsWindow(hWnd) || GetSystemMetrics(SM_CXMIN) > nWidth 
	   || GetSystemMetrics(SM_CYMIN) > nHeight) 
	{
		m_hLastErr = E_INVALIDARG;
		return false;
	}

	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(!m_pD3D) {
		return false;
	}
	
	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));
	
	d3dpp.BackBufferWidth = nWidth;
	d3dpp.BackBufferHeight = nHeight;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = TRUE;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	
	m_hLastErr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
						 hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pDev);
	if(FAILED(m_hLastErr)) {
		return false;
	}
	
//	m_hLastErr = m_pDev->GetSwapChain(0, &m_pSC);
//	m_pSC->GetPresentParameters(m_pDPP);
	
	SetStates();
	
//	SetMatrix();

	D3DXVECTOR3 pos(0.f, 10.f, -15.f);
	float fAspect = (float)nWidth/(float)nHeight;
	m_pCam = new CCamera();
	m_pCam->Init(&pos, fAspect);
	
	InitLight();
	
	return true;
}

void CRender::Render() {
	m_hLastErr = m_pDev->TestCooperativeLevel();
	if(FAILED(m_hLastErr)) return;
	
	m_pCam->Update(1.f);
	
	D3DXMATRIX* pView = m_pCam->get_View();
	D3DXMATRIX* pPrj = m_pCam->get_Proj();
	SetMatrix(pView, pPrj);
	
	m_pDev->Clear(0, nullptr, D3DCLEAR_TARGET, BLACK, 1.f, 0);
	
	m_pDev->BeginScene();
//		m_pDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 6);
		m_pDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, nVertCntIL, 0, 6);
	m_pDev->EndScene();
	
	m_pDev->Present(nullptr, nullptr, nullptr, nullptr);
}

void CRender::Destroy() {
	if(m_pCam) {
		m_pCam->Destroy();
		delete m_pCam;
		m_pCam = nullptr;
	}
	
	if(m_pDPP) {
		m_pDPP = nullptr;
	}
	
	if(m_pSC) {
		m_pSC->Release();
		m_pSC = nullptr;
	}
	
	if(m_pText) {
		m_pText->Release();
		m_pText = nullptr;
	}
	
	if(m_pIB) {
		m_pIB->Release();
		m_pIB = nullptr;
	}
	
	if(m_pVB) {
		m_pVB->Release();
		m_pVB = nullptr;
	}
	
	if(m_pDev) {
		m_pDev->Release();
		m_pDev = nullptr;
	}
	
	if(m_pD3D) {
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

void CRender::CreateCub() {
	m_hLastErr = m_pDev->CreateVertexBuffer(nVertCntIL*sizeof(Vertex), D3DUSAGE_WRITEONLY, 
						 FVF, D3DPOOL_DEFAULT, &m_pVB, nullptr);
	if(FAILED(m_hLastErr)) return;
	
	m_hLastErr = m_pDev->CreateIndexBuffer(nIdxCntL*sizeof(s16), D3DUSAGE_WRITEONLY,
						 D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, nullptr);
	if(FAILED(m_hLastErr)) return;
	
	LPVOID* pTmp = nullptr;
	m_pVB->Lock(0, 0, (LPVOID*)&pTmp, 0);
		memcpy_s(pTmp, sizeof(verticesILT), verticesILT, sizeof(verticesILT));
	m_pVB->Unlock();
	
	pTmp = nullptr;
	m_pIB->Lock(0, 0, (LPVOID*)&pTmp, 0);
		memcpy_s(pTmp, sizeof(IndexL), IndexL, sizeof(IndexL));
	m_pIB->Unlock();
	
	m_pDev->SetFVF(FVFLT);
	m_pDev->SetStreamSource(0, m_pVB, 0, sizeof(VertexLT));
	m_pDev->SetIndices(m_pIB);
	
	// Texturing
	m_hLastErr = D3DXCreateTextureFromFileW(m_pDev, L".\\test.jpg", &m_pText);
	if(FAILED(m_hLastErr)) return;
	
	m_pDev->SetTexture(0, m_pText);
}

void CRender::SetMatrix(D3DXMATRIX* pView, D3DXMATRIX* pPrj) {
	if(!pView || !pPrj) return;
	
	D3DXMATRIX mat;	
	D3DXMatrixIdentity(&mat);
	
//	D3DXMatrixRotationY(&mat, D3DXToRadian(45));
	m_pDev->SetTransform(D3DTS_WORLD, &mat);
	
//	D3DXMatrixIdentity(&mat);
//	D3DXMatrixLookAtLH(&mat, &D3DXVECTOR3(0.f, 10.f, -15.f), 
//					   &D3DXVECTOR3(0.f, 0.f, 0.f), &D3DXVECTOR3(0.f, 1.f, 0.f));
	m_pDev->SetTransform(D3DTS_VIEW, pView);
	
//	D3DXMatrixIdentity(&mat);
//	D3DXMatrixPerspectiveFovLH(&mat, D3DXToRadian(45.f), (float)nWidth/(float)nHeight, 
//							   1.f, 25.f);
	m_pDev->SetTransform(D3DTS_PROJECTION, pPrj);
}

void CRender::SetStates() {
	m_pDev->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
//	m_pDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
//	m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	// Light
	m_pDev->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
//	m_pDev->SetRenderState(D3DRS_LIGHTING, FALSE);
//	m_pDev->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
	m_pDev->SetRenderState(D3DRS_AMBIENT, GREEN);
	
	/** -- // Blending
	m_pDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	**/
}

void CRender::InitLight() {
	D3DMATERIAL9 mtl;
	memset(&mtl, 0, sizeof(mtl));
	
	mtl.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f); // White
	mtl.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	
	m_pDev->SetMaterial(&mtl);
	
	D3DLIGHT9 light;
	memset(&light, 0, sizeof(light));
	
	// Directional
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Direction = D3DXVECTOR3(-1.f, 0.f, 0.f);
	light.Diffuse = D3DXCOLOR(1.f, 0.f, 0.f, 1.f); // Red
	
	m_pDev->SetLight(0, &light);
	m_pDev->LightEnable(0, TRUE);
	
	// Point
	memset(&light, 0, sizeof(light));
	light.Type = D3DLIGHT_POINT;
	light.Position = D3DXVECTOR3(-1.5f, 1.5f, -1.f);
	light.Range = 50.f;
	light.Attenuation1 = 0.125f;
	light.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f); // Half-white
	
	m_pDev->SetLight(1, &light);
	m_pDev->LightEnable(1, TRUE);
	
	/** -- // Spot
	memset(&light, 0, sizeof(light));
	light.Type = D3DLIGHT_SPOT;
	light.Position = D3DXVECTOR3(-1.5f, 5.f, -1.5f);
	light.Direction = D3DXVECTOR3(0.f, -1.f, 0.f);
	light.Range = 50.f;
	light.Attenuation1 = 0.125f;
	light.Phi = D3DXToRadian(40.f);
	light.Theta = D3DXToRadian(20.f);
	light.Falloff = 1.f;
	light.Diffuse = D3DXCOLOR(1.f, 0.5f, 0.5f, 1.f);
	
	m_pDev->SetLight(2, &light);
	m_pDev->LightEnable(2, TRUE);
	**/
}

// Input handle
void CRender::OnInput() {
	MessageBoxExW(nullptr, L"Key pressed!", L"Inf", MB_ICONASTERISK, 0);
}

void CRender::OnKeyDown(WPARAM key) {
	switch(key) {
		case K_ESC:
			MessageBoxExW(nullptr, L"'ESC' pressed!", L"Inf", MB_ICONASTERISK, 0);
			break;
//		case K_W:
//			MessageBoxExW(nullptr, L"'W' pressed!", L"Inf", MB_ICONASTERISK, 0);
//			break;
//		case K_S:
//			MessageBoxExW(nullptr, L"'S' pressed!", L"Inf", MB_ICONASTERISK, 0);
//			break;
	}
}