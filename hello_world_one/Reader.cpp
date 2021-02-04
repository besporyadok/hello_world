#include "Reader.h"

#include <StdLib.h> // for _MAX_FNAME ? !!

CReader::CReader() {
	m_hFile = nullptr;
	m_hMap = nullptr;
	m_pData = nullptr;
	m_nPos = -1;
	m_nSize = -1;
	m_liSize = {0}; // Problem in VC++ 16.0
}

CReader::CReader(LPTSTR lpszFN) {
	if(!Open(lpszFN)) {
		m_hFile = nullptr;
		m_hMap = nullptr;
		m_pData = nullptr;
		m_nPos = -1;
		m_nSize = -1;
		m_liSize = {0};
	}
}

bool CReader::Open(LPTSTR lpszFN) {
	DWORD dwAttr = GetFileAttributes(lpszFN);
	
	if((dwAttr == INVALID_FILE_ATTRIBUTES) || (dwAttr & FILE_ATTRIBUTE_DIRECTORY)) 
		return false;
	
	m_hFile = CreateFile(lpszFN, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(m_hFile == INVALID_HANDLE_VALUE) return false;
	
	GetFileSizeEx(m_hFile, &m_liSize);
	if(m_liSize.HighPart) return false;
	m_nSize = m_liSize.LowPart;
	
	m_hMap = CreateFileMapping(m_hFile, NULL, PAGE_READONLY, 0, m_liSize.LowPart, NULL);
	if(m_hMap == INVALID_HANDLE_VALUE) return false;
	
	m_pData = reinterpret_cast<char*>(MapViewOfFileEx(m_hMap, FILE_MAP_READ, 0, 0, m_liSize.LowPart, NULL));
	if(!m_pData) return false;
	
	m_nPos = 0;
	
	return true;
}

void CReader::Close() {
	if(!m_hFile) return;
	
	if(m_pData) {
		UnmapViewOfFile(m_pData);
		m_pData = nullptr;
	}
	
	if(m_hMap) {
		CloseHandle(m_hMap);
		m_hMap = nullptr;
	}
	
	CloseHandle(m_hFile);
	m_hFile = nullptr;
	
	m_liSize = {0};
	m_nSize = -1;
}

void CReader::Seek(short nPos) {
	if(nPos < 0 || nPos > m_nSize)
		return;
	
	m_nPos = nPos;
}

void CReader::Advance(short nPos) {
	if(nPos < 0 || m_nPos+nPos > m_nSize)
		return;
	
	m_nPos += nPos;
}

void CReader::r(LPVOID lpDest, int nSize) {
	if(!lpDest || nSize <= 0 || m_nPos+nSize > m_nSize) 
		return;
	
	CopyMemory(lpDest, Ptr(), nSize);
	Advance(nSize);
}

// †есть, как она есть xD
void CReader::r_chunks_dump() {
	DWORD dwUnused = 0;
	char* pBuf = nullptr;
	TCHAR lpszFN[MAX_PATH];
	TCHAR lpszTmp[_MAX_FNAME];
	
	GetCurrentDirectory(MAX_PATH, lpszFN);
	StringCchCat(lpszFN, MAX_PATH, TEXT("\\Chunks\\Chunk_%X.bin"));
	
	DWORD dwAttr = GetFileAttributes(TEXT("Chunks"));	
	if(dwAttr == INVALID_FILE_ATTRIBUTES) {
		CreateDirectory(TEXT("Chunks"), NULL);
	}
	
	while(!Eof()) {
		DWORD dwID = r_u32();
		DWORD dwSize = r_u32();
		
		StringCchPrintfEx(lpszTmp, _MAX_FNAME, NULL, 
						  NULL, 0, lpszFN, dwID);
		
		HANDLE hFile = CreateFile(lpszTmp, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if(hFile == INVALID_HANDLE_VALUE) break;
		
		WriteFile(hFile, &dwID, sizeof(DWORD), &dwUnused, NULL);
		WriteFile(hFile, &dwSize, sizeof(DWORD), &dwUnused, NULL);
		
		pBuf = new char[dwSize];
		r(pBuf, dwSize);
		WriteFile(hFile, pBuf, dwSize, &dwUnused, NULL);
		delete[] pBuf;
		
		CloseHandle(hFile);
		hFile = nullptr;
		
		Advance(dwSize);
	}
}