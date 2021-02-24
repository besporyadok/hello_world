#pragma once

#define _X86_
#include <WinDef.h>
#include <WinBase.h>

class CTimer {
	public:
		CTimer();
	
		inline float GetElapsed(void) const { return m_fElapsTime; }
		inline double GetFreq(void) const { return m_llFreq; }
		
		void Start();
		void Update();
		void Reset();
		
	private:
		CTimer(const CTimer&) {}
		CTimer& operator= (const CTimer&) {}
		
	private:
		bool m_fStarted;
		double m_llFreq;
		double m_llLastTime, m_llCurTime;
		float m_fElapsTime;
};