#ifndef __XRAYSYNC_H__
#define __XRAYSYNC_H__

class XRCORE_API xrCriticalSection {
private:
	void*				pmutex;
#ifdef PROFILE_CRITICAL_SECTIONS
	LPCSTR				m_id;
#endif // PROFILE_CRITICAL_SECTIONS

public:
#ifdef PROFILE_CRITICAL_SECTIONS
    xrCriticalSection	(LPCSTR id);
#else // PROFILE_CRITICAL_SECTIONS
    xrCriticalSection	();
#endif // PROFILE_CRITICAL_SECTIONS
    ~xrCriticalSection	();

    void				Enter	();
    void				Leave	();
	BOOL				TryEnter();
};

#endif