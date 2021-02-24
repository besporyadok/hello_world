#include "timer.hpp"

CTimer::CTimer() {
	LARGE_INTEGER tmp;
	
	QueryPerformanceFrequency(&tmp);
	m_llFreq = tmp.QuadPart;
	
	Reset();
}

void CTimer::Start() {
	if(m_fStarted) return;
	
	LARGE_INTEGER tmp;
	
	QueryPerformanceCounter(&tmp);
	m_llLastTime = m_llCurTime = tmp.QuadPart;
	
	m_fStarted = true;
}

void CTimer::Update() {
	m_llLastTime = m_llCurTime;
	
	LARGE_INTEGER tmp;
	QueryPerformanceCounter(&tmp);
	
	m_llCurTime = tmp.QuadPart;
	m_fElapsTime = (float)((double)(m_llCurTime - m_llLastTime) / (double)m_llFreq);
	
	if(m_fElapsTime < 0.0f) 
		m_fElapsTime = 0.0f;
}

void CTimer::Reset() {
	m_llCurTime = m_llLastTime = 0;
	m_fElapsTime = 0.f;
	m_fStarted = false;
}