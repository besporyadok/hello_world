#define _UNICODE
#include <TChar.h>

#include "Str.h"
#include "Reader.h"

#include "Debug.h"

void Lab_str() {
	wchar_t* test = L"";
	size_t test1 = 0, test11 = 0;
	bool test2 = false;

	CStrT<wchar_t> str1;
	CStrT<wchar_t> str2(L"Lil22832");
	CStrT<wchar_t> str3(str2);
	
	test = str2.c_str();
	test1 = str2.len();
	test11 = str2.size();
	test2 = str1.empty();
	
	(!(test1 == test11)) ? (test2 = true) : (test2 = false);
	
	if(!str3.empty()) {
		test = str3.c_str();
		test1 = str3.len();
	}
	
	DBG_BREAK;

	CStrT<wchar_t> str4(L"San-DiegoTsT\n"); // 13+1 smbl
	str3 = str4;
	str4 = L"lollollollolll0x23";
}

void Lab_read() {
	LPTSTR lpTest = nullptr;
	unsigned nTest = 0;
	
	DBG_BREAK;
	
	CReader read(TEXT("level.geom"));
	read.r_chunks_dump();
}

void __cdecl Lab(void) {
	LPTSTR lpszCmdLn = GetCommandLine();
	
	if(!IsDebuggerPresent()) return;
	
	if(_tcsstr(lpszCmdLn, TEXT("-tString"))) {
		Lab_str();
		return;
	}
	
	if(_tcsstr(lpszCmdLn, TEXT("-tReader"))) {
		Lab_read();
		return;
	}
}