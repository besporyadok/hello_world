#include "MainWindow.h"

INT_PTR CMainWindow::AboutProc(HWND hDlg, UINT uMsg, WPARAM, LPARAM) {
	switch(uMsg) {
		case WM_INITDIALOG:
			SetDlgItemTextW(hDlg, 0x228, L"It lil program for educational purposes!\nAuthor: K4R");
			break;
		case WM_CLOSE:
			EndDialog(hDlg, 0);
			break;
	}
	
	return 0;
}