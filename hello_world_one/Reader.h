#ifndef __READER_H__
#define __READER_H__

#define _X86_
#include <WinDef.h>
#include <WinBase.h>
#include <StrSafe.h>

class CReader {
	public:
		CReader();
		volatile CReader(LPTSTR lpszFN);
		~CReader() { Close(); }
		
		// Not create in heap
		void* operator new(size_t) = delete; // Not compability with VC++ 16.0 (VS 10.0)
		void operator delete(void*) = delete;
		
		bool Open(LPTSTR lpszFN);
		
		void Seek(short nPos);
		void Advance(short nPos);
		int Eps() const { return m_nSize - m_nPos; }
		bool Eof() const { return Eps() <= 0; }
		void Reset() { m_nPos = 0; }
		
		void r(LPVOID lpDest, int nSize);
		unsigned r_u32() { unsigned tmp; r(&tmp, sizeof(tmp)); return tmp; }
		void r_chunks_dump();
		
		void Close();
		
	private:
		// Singleton
		CReader(const CReader&) {}
		CReader& operator=(const CReader&) {}
		
		// AUCHTUNG !!! - Use only Read mthd!
		LPVOID Ptr() const { return &(m_pData[m_nPos]); }
		
		HANDLE m_hFile;
		LARGE_INTEGER m_liSize; // ?
		int m_nSize;
		HANDLE m_hMap;
		
		int m_nPos;
		char* m_pData;
};

#endif