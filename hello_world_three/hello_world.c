/*** -- Inf
class DDConfig {
	bool bInvalid;
	bool bLoaded; ?
	void* pVSBlob;
};

VS_BLOB {
	dword Size = A4; (dec: 164b/84b)
	char Data[Size];
};

struct DataOne {
	0x0: int nHyiZnaet (edition?) = 0x13;
	0x14: int nCode;
	0x9c: short sYear; >= CurYers
	0x9e: short sMonth; >= CurMonth
	0xA0: short sDay; > CurDay
};

struct DataTwo {
	0x0: int nCode; // 0x228
	0x34: int nEdition; = 0x13
	0x44: short sYear; != FFFF
	0x46: short sMonth;
	0x48: short sDay;
	0x50: bool bReserved = false;
	0x51: bool bReserved = true;
};
***/

#define _X86_
#define SAL_NO_ATTRIBUTE_DECLARATIONS
#include <stddef.h>
#include <WinDef.h>
#include <WinBase.h>
#include <WinUser.h>
#include <WinReg.h>
#include <WinCrypt.h>
#include <StrSafe.h>

#pragma comment(lib, "AdvAPI32")
#pragma comment(lib, "User32")
#pragma comment(lib, "Crypt32")

#define RESERVED 132
#pragma pack(push, 1)
typedef struct _DataOne {
	int nEdition; // 0x0
	char Reserved[16]; // 0x4
	int nCode; // 0x14
	char Reserved1[RESERVED];
	short sYearExp; // 0x9C
	short sMonthExp;
	short sDayExp;
} DataOn, *lpDataOn;

typedef struct _DataTwo {
	int nCode; // 0x0
	char Padding0[48];
	int nEdition; // 0x34
	char Padding1[8];
	int Padding2;
	short sYear; // 0x44
	short sMonth; // 0x46
	short sDay; // 0x48
	int Padding3;
	char Padding4[2];
	char fReserved; // 0x50
	char fReserved1; // 0x51
} DataTwo, *lpDataTwo;
#pragma pack(pop)

typedef enum _DataType {
	DATA_ONE = 0,
	DATA_TWO
} DataType;

static HANDLE g_hLog = NULL;

VOID Msg(LPSTR lpszMsg, ...) {
	va_list va = NULL;
	DWORD dwLen = 0, dwUnused = 0;
	CHAR szMsgOut[MAX_PATH];
	
	if(g_hLog == INVALID_HANDLE_VALUE)
		return;
	
	va_start(va, lpszMsg);
		dwLen = _vscprintf(lpszMsg, va);
		StringCchVPrintfA(szMsgOut, dwLen+1, lpszMsg, va);
	va_end(va);
	
	WriteFile(g_hLog, szMsgOut, dwLen, &dwUnused, NULL);
}

VOID MsgSysErr(LPSTR lpszMsg) {
	LPSTR lpszErrMsg = NULL;
	LONG lStatus = 0L;
	
	Msg("[ERR]:\tSystem error (%s):\n", lpszMsg);
	
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, 
				  NULL, GetLastError(), 0, (LPSTR)&lpszErrMsg, MAX_PATH, NULL);
	
	Msg("\t%s", lpszErrMsg);
	
	__asm {
		mov eax, fs:[18h]
		mov eax, [eax+0BF4h]
		mov lStatus, eax
	};
	
	Msg("\tLast NTSTATUS: (0x%X).\n", lStatus);
				  
	if(lpszErrMsg) {
		LocalFree(lpszErrMsg);
	}
}

VOID InitLog() {
	SYSTEMTIME time;
	
	g_hLog = CreateFileA("Out.log", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(g_hLog != INVALID_HANDLE_VALUE) {
		ZeroMemory(&time, sizeof(SYSTEMTIME));
		GetSystemTime(&time);
		
		Msg("Startup program. Date: [%2d.%2d.%4d]\n", time.wDay, time.wMonth, time.wYear);
	}
}

VOID PrintStructInf() {
	Msg("[DBG]:\tStructure info:\nStruct DataTwo {\n");
	
	Msg("\t0x%X:\t%s\n", offsetof(DataTwo, nCode), "nCode");
	Msg("\t0x%X:\t%s\n", offsetof(DataTwo, Padding0), "Padding0");
	Msg("\t0x%X:\t%s\n", offsetof(DataTwo, nEdition), "nEdition");
	Msg("\t0x%X:\t%s\n", offsetof(DataTwo, Padding1), "Padding1");
	Msg("\t0x%X:\t%s\n", offsetof(DataTwo, Padding2), "Padding2");
	Msg("\t0x%X:\t%s\n", offsetof(DataTwo, sYear), "sYear");
	Msg("\t0x%X:\t%s\n", offsetof(DataTwo, sMonth), "sMonth");
	Msg("\t0x%X:\t%s\n", offsetof(DataTwo, sDay), "sDay");
	Msg("\t0x%X:\t%s\n", offsetof(DataTwo, Padding3), "Padding3");
	Msg("\t0x%X:\t%s\n", offsetof(DataTwo, Padding4), "Padding4");
	Msg("\t0x%X:\t%s\n", offsetof(DataTwo, fReserved), "fReserved");
	Msg("\t0x%X:\t%s\n", offsetof(DataTwo, fReserved1), "fReserved1");
	
	Msg("}\n");
}

VOID MakeDataTwo(lpDataTwo Data) {
	int nIdx = 0;
	
	Data->nCode = 0x228;
	Data->nEdition = 0x13;
	Data->sYear = 2022;
	Data->sMonth = 10;
	Data->sDay = 20;
	Data->fReserved = 0;
	Data->fReserved1 = 1;
}

VOID MakeDataOn(lpDataOn Data) {
	int i = 0;
	SYSTEMTIME time;
	
	ZeroMemory(&time, sizeof(SYSTEMTIME));
	GetSystemTime(&time);
	
	Data->nEdition = 0x13;
	Data->sYearExp = time.wYear+1;
	Data->sMonthExp = time.wMonth;
	Data->sDayExp = time.wDay;
	Data->nCode = 0x228;
	
	for(i = 0; i < RESERVED; i++)
		Data->Reserved1[i] = -1;
}

BOOL SetReg(LPVOID Data, DWORD dwLen, DataType eType) {
	BOOL bRet = FALSE;
	CHAR lpszKeyRoot[MAX_PATH];
	HKEY hKey = NULL;
	
	StringCchCopyExA(lpszKeyRoot, MAX_PATH, "Licenses\\0B47443B-87E1-43c2-8AF7-3B82E8574FF6\\", NULL, NULL, 0);
	
	switch(eType) {
		case DATA_ONE:
			StringCchCatExA(lpszKeyRoot, MAX_PATH, "0bcad", NULL, NULL, 0);
			break;
		case DATA_TWO:
			StringCchCatExA(lpszKeyRoot, MAX_PATH, "00552", NULL, NULL, 0);
			break;
		default:
			return bRet;
			break;
	}
	
	if(!RegOpenKeyExA(HKEY_CLASSES_ROOT, lpszKeyRoot, 0, KEY_SET_VALUE, &hKey)) {
		if(!RegSetValueExA(hKey, NULL, 0, REG_BINARY, Data, dwLen)) {
			bRet = TRUE;
		}
		
		RegCloseKey(hKey);
		hKey = NULL;
	}
	
	return bRet;
}

VOID Dump(LPVOID Data, DWORD dwLen) {
	HANDLE hFile = NULL;
	DWORD dwUnused = 0;
	
	hFile = CreateFile("Out.bin", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return;
	
	WriteFile(hFile, Data, dwLen, &dwUnused, NULL);
	
	CloseHandle(hFile);
	hFile = NULL;
}

INT WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLn, INT nCmdShow) {
	BOOL bRet = FALSE;
	DATA_BLOB dData, dOut;
	DataOn data;
	DataTwo dataEx;
	
	InitLog();
	PrintStructInf();
	
	MakeDataOn(&data);
	dData.cbData = 164;
	dData.pbData = (LPBYTE)&data;
	
	bRet = CryptProtectData(&dData, NULL, NULL, NULL, NULL, 0, &dOut);
	if(bRet) {
		Msg("[INF]:\tCRYPT data one suceeded!\n");
		
		if(!SetReg(dOut.pbData, dOut.cbData, DATA_ONE)) {
			MsgSysErr("SetReg FAILURE!");
		}
			
		LocalFree(dOut.pbData);
	}
	
	// TWO Data
	MakeDataTwo(&dataEx);
	dData.cbData = 84;
	dData.pbData = (LPBYTE)&dataEx;
	
	bRet = CryptProtectData(&dData, NULL, NULL, NULL, NULL, 0, &dOut);
	if(bRet) {
		Msg("[INF]:\tCRYPT data two suceeded!\n");
		
		if(!SetReg(dOut.pbData, dOut.cbData, DATA_TWO)) {
			MsgSysErr("SetReg2 FAILURE!");
		}
		
		LocalFree(dOut.pbData);
	}
	
	if(g_hLog != INVALID_HANDLE_VALUE) {
		CloseHandle(g_hLog);
		g_hLog = NULL;
	}
	
	return 0;
}