#include "camera.hpp"

CCamera::CCamera() {
	m_fAspect = m_fVelocity = 0.f;
	m_pLook = D3DXVECTOR3(0.f, 0.f, 0.f);
}

void CCamera::Init(D3DXVECTOR3* pos, float fAspect) {
	g_pInput->Register(this);
	
	m_pPos = *pos;
	m_fAspect = fAspect;
	m_fVelocity = 0.5f;
	
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixIdentity(&m_mtxProj);
}

void CCamera::Destroy() {
	g_pInput->UnRegister(this);
}

void CCamera::OnKeyDown(WPARAM wKey) {
	switch(wKey) {
		case K_W:
			m_pPos.z += 1.f;
			break;
		case K_S:
			m_pPos.z -= 1.f;
			break;
		case K_A:
			m_pPos.x -= 1.f;
			break;
		case K_D:
			m_pPos.x += 1.f;
			break;
	}
}

void CCamera::Update(float fElapsed) {
	D3DXVECTOR3 vPos;
	vPos = m_pPos * m_fVelocity;
	
	D3DXMatrixLookAtLH(&m_mtxView, &vPos, &m_pLook, &D3DXVECTOR3(0.f, 1.f, 0.f));
	D3DXMatrixPerspectiveFovLH(&m_mtxProj, D3DXToRadian(45.f), m_fAspect, 1.f, 25.f);
}