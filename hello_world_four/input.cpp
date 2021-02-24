#include "input.hpp"

IInputListener* g_pInput = nullptr;

CInputListener::CInputListener() {}

CInputListener::~CInputListener() {
	Clear();
}

void CInputListener::Register(IInput* el) {
	if(IsExist(el)) return;
	
	m_pObservers.push_back(el);
}

void CInputListener::UnRegister(IInput* el) {
	if(!IsExist(el)) return;
	
	m_pObservers.erase(m_pCurEl);
}

void CInputListener::Notify(SInputParams* ip) {
	if(!ip) return;
	
	switch(ip->action) {
		case IA_KEYDOWN:
			KeyDown(ip->wParam, ip->lParam);
			break;
	}
	
	/* for(it el = m_pObservers.begin(); el != m_pObservers.end(); el++) {
		(*el)->OnInput();
	} */
}

bool CInputListener::IsExist(IInput* el) {
	if(!el) return false;
	
	if(m_pObservers.empty()) return false;
	
	m_pCurEl = std::find(m_pObservers.begin(), m_pObservers.end(), el);
	
	if(m_pCurEl == m_pObservers.end()) return false;
	
	return true; 
}

void CInputListener::Clear() {
	m_pObservers.clear();
}

void CInputListener::KeyDown(WPARAM wParam, LPARAM lParam) {
	for(it el = m_pObservers.begin(); el != m_pObservers.end(); el++) {
		(*el)->OnKeyDown(wParam);
	}
}