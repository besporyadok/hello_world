#pragma pack(push, 4)
struct EL_Base {
	DWORD style;
	DWORD dwExtendedStyle;
	short x;
	short y;
	short cx;
	short cy;
	WORD  id; // DLGITEMTEMPLATE_END
	WORD wSysClass;
	WORD wIdClass;
};

struct AboutDialog {
	DWORD style;
	DWORD dwExtendedStyle;
	WORD  cdit;
	short x;
	short y;
	short cx;
	short cy; // DLGTEMPLATE_END
	WORD wMenu;
	WORD wWindowClass;
	WCHAR wszTitle[6];
		
	struct {
		EL_Base base;
		WCHAR wszTitle[1];
		WORD cbCreationData;
	} text;
	
	#define ELB(dlg, el) dlg.el.base
};
#pragma pack(pop)