#pragma once

#include "iinput.hpp"
#include <vector>
#include <algorithm>

class CInputListener : public IInputListener {
	typedef std::vector<IInput*>::iterator it;
	typedef std::vector<IInput*>::const_iterator cit;
	
	public:
		CInputListener();
		virtual ~CInputListener();
		
	public:
		void Register(IInput* el);
		void UnRegister(IInput* el);
		void Notify(SInputParams* ip);
		
	private:
		CInputListener(const CInputListener&) {}
		CInputListener& operator= (const CInputListener&) {}
		
	private:
		void Clear();
		bool IsExist(IInput* el);
		
		void KeyDown(WPARAM wParam, LPARAM lParam);
	
		std::vector<IInput*> m_pObservers;
		cit m_pCurEl;
};

extern IInputListener* g_pInput;