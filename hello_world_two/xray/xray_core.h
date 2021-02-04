#ifndef __XRAYCORE_H__
#define __XRAYCORE_H__

typedef void (*LogCallback) (LPCSTR string);

class XRCORE_API xrCore  {
	public:
		string64	ApplicationName;
		string_path	ApplicationPath;
		string_path	ApplicationDataPath;
		string_path	WorkingPath;
		string64	UserName;
		string64	CompName;
		string512	Params;

	public:
		void		_initialize	(LPCSTR ApplicationName, LogCallback cb=nullptr, BOOL init_fs=TRUE, LPCSTR fs_fname=nullptr);
		void		_destroy	();
};

void XRCORE_API	__cdecl Msg(LPCSTR format, ...);
void XRCORE_API	Log(LPCSTR msg);
void XRCORE_API	Log(LPCSTR msg);
void XRCORE_API	Log(LPCSTR msg, LPCSTR	dop);
void XRCORE_API	Log(LPCSTR msg, u32 dop);
void XRCORE_API	Log(LPCSTR msg, int dop);
void XRCORE_API	Log(LPCSTR msg, float dop);
void XRCORE_API	Log(LPCSTR msg, const Fvector& dop);
void XRCORE_API	Log(LPCSTR msg, const Fmatrix& dop);
void XRCORE_API	LogWinErr(LPCSTR msg, long err_code);

void XRCORE_API SetLogCB(LogCallback cb);
void XRCORE_API	FlushLog();

extern XRCORE_API xr_vector<shared_str> LogFile;
extern XRCORE_API BOOL LogExecCB;

extern XRCORE_API xrCore Core;

#endif