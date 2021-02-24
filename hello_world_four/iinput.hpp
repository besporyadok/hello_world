#pragma once

#define _X86_
#include <WinDef.h>

enum EKeys {
	K_W = 0x57,
	K_S = 0x53,
	K_A = 0x41,
	K_D = 0x44,
	K_ESC = 0x1B,
	K_INVALID = 0xFFFFFFFF
};

enum EInputActions {
	IA_KEYDOWN = 0x0,
	IA_INVALID = 0xFFFFFFFF
};

struct SInputParams {
	EInputActions action;
	WPARAM wParam;
	LPARAM lParam;
};

struct IInput {
	virtual void OnInput(void) = 0;
	virtual void OnKeyDown(WPARAM) = 0;
};

struct IInputListener {
	virtual void Register(IInput*) = 0;
	virtual void UnRegister(IInput*) = 0;
	virtual void Notify(SInputParams*) = 0;
};