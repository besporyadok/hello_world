#pragma once

#include <d3dx9.h>

#include "input.hpp"

class CCamera : public IInput {
	public:
		CCamera();
		
		inline D3DXMATRIX* get_View(void) { return &m_mtxView; }
		inline D3DXMATRIX* get_Proj(void) { return &m_mtxProj; }
		
		void Init(D3DXVECTOR3* pos, float fAspect);
		void Update(float fElapsed);
		void Destroy();
		
		void OnInput() {}
		void OnKeyDown(WPARAM wKey);
		
	private:
		CCamera(const CCamera&) {}
		CCamera& operator= (const CCamera&) {}
		
	private:
		float m_fAspect;
		float m_fVelocity;
		D3DXMATRIX m_mtxView, m_mtxProj;
		D3DXVECTOR3 m_pEye, m_pLook, m_pPos;
};