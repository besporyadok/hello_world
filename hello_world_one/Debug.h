#ifndef __DEBUG_H__
#define __DEBUG_H__

#pragma comment(lib, "DxErr")

#include <Windows.h>
#include <DxErr.h>
// Duplicate include! Use PCH? (See: Engine.h, D3D9.h)
#include <StdIO.h>

#define DXASSERT(expr) { \
	HRESULT hr = expr; \
	if(FAILED(hr)) Dbg.Suicide(hr); \
}

#define DBG_BREAK __asm int 3h;

LPTSTR const DbgPrefix[3] {
	TEXT("[INF]:\t"),
	TEXT("[WARN]:\t"),
	TEXT("[ERR]:\t")
};

enum DbgLvl {
	INFO = 0,
	WARN = 1,
	ERR = 2,
	INV = 0xFF
};

class CDebug {
	public:
		CDebug() : m_fInit(false), m_hLog(NULL) {}
	
		void Init(LPTSTR lpszLogName);
		void Msg(LPTSTR lpszMsg);
		void MsgEx(LPTSTR lpszMsg, ...);
		void Suicide(HRESULT hr);
		void Destroy();
	
	private:
		bool   m_fInit;
		HANDLE m_hLog;
};

extern CDebug Dbg;

#endif