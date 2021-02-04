#ifndef __STR_H__
#define __STR_H__

#define _X86_
#include <WinDef.h>
#include <WinBase.h>

// Declaration
template <class T>
class CStrT {
	typedef T type;
	typedef T* const cstr;
	typedef CStrT<T> Self;
	
	public:
		CStrT();
		volatile CStrT(cstr str);
		CStrT(Self& obj);
		~CStrT();
		
		Self& operator=(const Self& obj);
		Self& operator=(cstr str);
		
		type* c_str(void) const { return m_str; }
		size_t len(void) const { return m_len; }
		size_t size(void) const { return m_len*sizeof(T); }
		bool empty(void) const;
		
	private:
		void Init(void);
		bool IsValidStrPtr(cstr str) const;
		void Alloc(size_t size);
		void ReAlloc(size_t size);
		void Assign(cstr str, bool bRA = false);
		void Copy(cstr str);
		void Free(void);
		size_t Len(cstr str) const;
	
		type* m_str;
		size_t m_len;
		
		HANDLE m_hHeap;
};

// Implementation
template<class T>
CStrT<T>::CStrT() {
	Init();
}

template<class T>
CStrT<T>::CStrT(cstr str) {
	Init();
	
	Assign(str);
}

template<class T>
CStrT<T>::CStrT(Self& obj) {
	Init();
	
	if(!obj.empty()) {
		Assign(obj.m_str);
	}
}

template<class T>
CStrT<T>::~CStrT() {
	Free();
}

template<class T>
CStrT<T>& CStrT<T>::operator=(const CStrT<T>& obj) {
	Init();
	
	if(!obj.empty()) {
		Assign(obj.m_str);
	}
	
	return *this;
}

template<class T>
CStrT<T>& CStrT<T>::operator=(cstr str) {
	Assign(str, true);
	
	return *this;
}

template<class T>
size_t CStrT<T>::Len(cstr str) const {
	if(!IsValidStrPtr(str))
		return -1;
	else return static_cast<size_t>((lstrlen(str))+1);
}

template<class T>
bool CStrT<T>::IsValidStrPtr(cstr str) const {
	if(str != nullptr && str[0] != 0)
		return true;
	else
		return false;
}

template<class T>
void CStrT<T>::Alloc(size_t size) {
	if(!m_hHeap) return;
	
	m_str = reinterpret_cast<type*>(HeapAlloc(m_hHeap, HEAP_ZERO_MEMORY, size));
}

template<class T>
void CStrT<T>::ReAlloc(size_t size) {
	if(!m_hHeap || !m_str || !size) return;
	
	HeapReAlloc(m_hHeap, HEAP_ZERO_MEMORY, m_str, size);
}

template<class T>
void CStrT<T>::Init() {
	m_hHeap = GetProcessHeap();
	
	m_str = nullptr;
	m_len = -1;
}

template<class T>
void CStrT<T>::Free() {
	if(!m_hHeap || !m_str) return;
	
	HeapFree(m_hHeap, 0, m_str);
	
	m_str = nullptr;
	m_len = -1;
	m_hHeap = nullptr;
}

template<class T>
void CStrT<T>::Copy(cstr str) {
	if(!m_str || !IsValidStrPtr(str) || !m_len) return;
	
	CopyMemory(m_str, str, size());
}

template<class T>
bool CStrT<T>::empty() const {	
	return (!m_len || !IsValidStrPtr(m_str)) ? true : false;
}

template<class T>
void CStrT<T>::Assign(cstr str, bool bRA) {
	m_len = Len(str);
	
	if(bRA) {
		ReAlloc(size());
	} else {
		Alloc(size());
	}
	
	if(m_len) {
		Copy(str);
	}
}

#endif