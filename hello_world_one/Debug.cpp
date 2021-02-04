#include "Debug.h"

void CDebug::Init(LPTSTR lpszLogName) {
	if(!m_fInit) {
		m_hLog = CreateFile(lpszLogName, GENERIC_WRITE, 0, NULL, 
							CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		
		if(!m_hLog) return; // !
		
		m_fInit = true;
		
		Msg(TEXT("Dbg subsys init\n"));
	}
}

void CDebug::Destroy() {
	if(m_fInit) {
		Msg(TEXT("Dbg subsys destroy"));
		
		CloseHandle(m_hLog);
		m_hLog = NULL;
		m_fInit = false;
	}
}

void CDebug::Msg(LPTSTR lpszMsg) {
	if(m_fInit) {
		DWORD dwUnused = 0;
		
		WriteFile(m_hLog, lpszMsg, lstrlen(lpszMsg)*sizeof(WCHAR), &dwUnused, NULL);
	}
}

void CDebug::MsgEx(LPTSTR lpszMsg, ...) {
	LPTSTR lpBuf = NULL;
	va_list arg = NULL;
	int dwLen = 0;
	
	va_start(arg, lpszMsg);
	
	dwLen = _vscwprintf(lpszMsg, arg) + 1;
	lpBuf = static_cast<LPTSTR>(malloc(dwLen*sizeof(WCHAR)));
	
	if(lpBuf != NULL) {
		vswprintf_s(lpBuf, dwLen, lpszMsg, arg);
		
		Msg(lpBuf);
		
		free(lpBuf);
		lpBuf = NULL;
	}
	
	va_end(arg);
}

void CDebug::Suicide(HRESULT hr) {
	LPCTSTR lpszCode = NULL, lpszDesc = NULL;
	
	lpszCode = DXGetErrorString(hr);
	lpszDesc = DXGetErrorDescription(hr);
	
	MsgEx(TEXT("[FATAL ERROR]\n\tCode: 0x%X\n\tDesc: %s (%s)\nSuicide!\n"), hr, lpszCode, lpszDesc);	
	DXTRACE_ERR_MSGBOX(TEXT("!FATAL ERROR"), hr);
	
	abort();
}

CDebug Dbg;