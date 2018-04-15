#pragma once

#include <Windows.h>


// constants
static const WORD SPECIAL_SCANCODE = 0xe0;

static const WORD ARROW_UP_SCANCODE = 0x48;
static const WORD ARROW_LEFT_SCANCODE = 0x4b;
static const WORD ARROW_DOWN_SCANCODE = 0x50;
static const WORD ARROW_RIGHT_SCANCODE = 0x4d;
static const WORD TAB_SCANCODE = 0x0f;
static const WORD LEFT_ALT_SCANCODE = 0x38;
static const WORD ENTER_SCANCODE = 0x1c;
static const WORD ESC_SCANCODE = 0x01;
static const WORD F4_SCANCODE = 0x3e;

static const DWORD keypress_delay_ms = 10;


namespace WinInterface {

	void sendkey(WORD scan_code, bool tf_down_up, bool extended = false) {
		INPUT input = { 0 };
		input.type = INPUT_KEYBOARD;
		input.ki.wScan = scan_code;
		input.ki.dwFlags = KEYEVENTF_SCANCODE;
		if (!tf_down_up) input.ki.dwFlags |= KEYEVENTF_KEYUP;
		if (extended)    input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
		SendInput(1, &input, sizeof(input));
	}

	void keydown(WORD scan_code, bool extended = false) {
		sendkey(scan_code, true, extended);
	}

	void keyup(WORD scan_code, bool extended = false) {
		sendkey(scan_code, false, extended);
	}

	void mouseLeftButtonUp() {
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		Sleep(keypress_delay_ms);
	}

	void mouseLeftButtonDown() {
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		Sleep(keypress_delay_ms);
	}

	void mouseRightButtonUp() {
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		Sleep(keypress_delay_ms);
	}

	void mouseRightButtonDown() {
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
		Sleep(keypress_delay_ms);
	}

	void mouseWheelScrollUp() {
		mouse_event(MOUSEEVENTF_WHEEL, 0, 0, 10, 0);
		Sleep(keypress_delay_ms);
	}

	void mouseWheelScrollDown() {
		mouse_event(MOUSEEVENTF_WHEEL, 0, 0, -10, 0);
		Sleep(keypress_delay_ms);
	}

	void mouseLeftButtonClick() {
		mouseLeftButtonDown();
		mouseLeftButtonUp();
	}

	void mouseRightButtonClick() {
		mouseRightButtonDown();
		mouseRightButtonUp();
	}

	void enterKeyDown(){
		keydown(ENTER_SCANCODE);
	}

	void enterKeyUp() {
		keydown(ENTER_SCANCODE);
	}

	void enterKeyClick() {
		enterKeyDown();
		enterKeyUp();
	}

	void escapeKeyDown() {
		keydown(ESC_SCANCODE);
	}

	void escapeKeyUp() {
		keydown(ESC_SCANCODE);
	}

	void escapeKeyClick() {
		escapeKeyDown();
		escapeKeyUp();
	}

	void altTab(int tab_count = 1) {
		keydown(LEFT_ALT_SCANCODE);
		Sleep(keypress_delay_ms);
		for (int i = 0; i < tab_count; ++i) {
			keydown(TAB_SCANCODE);
			Sleep(keypress_delay_ms);
			keyup(TAB_SCANCODE);
			Sleep(keypress_delay_ms);
		}
		keyup(LEFT_ALT_SCANCODE);
	}

	void altKeyDown() {
		keydown(LEFT_ALT_SCANCODE);
		Sleep(keypress_delay_ms);
	}

	void altKeyUp() {
		keyup(LEFT_ALT_SCANCODE);
		Sleep(keypress_delay_ms);
	}

	void tabKeyClick() {
		keydown(TAB_SCANCODE);
		Sleep(keypress_delay_ms);
		keyup(TAB_SCANCODE);
		Sleep(keypress_delay_ms);
	}

	void arrowUpDown() {
		keydown(SPECIAL_SCANCODE);
		keydown(ARROW_UP_SCANCODE);
		Sleep(keypress_delay_ms);
	}

	void arrowLeftDown() {
		keydown(SPECIAL_SCANCODE);
		keydown(ARROW_LEFT_SCANCODE);
		Sleep(keypress_delay_ms);
	}

	void arrowDownDown() {
		keydown(SPECIAL_SCANCODE);
		keydown(ARROW_DOWN_SCANCODE);
		Sleep(keypress_delay_ms);
	}

	void arrowRightDown() {
		keydown(SPECIAL_SCANCODE);
		keydown(ARROW_RIGHT_SCANCODE);
		Sleep(keypress_delay_ms);
	}

	void arrowUpUp() {
		keyup(SPECIAL_SCANCODE);
		keyup(ARROW_UP_SCANCODE);
		Sleep(keypress_delay_ms);
	}

	void arrowLeftUp() {
		keyup(SPECIAL_SCANCODE);
		keyup(ARROW_LEFT_SCANCODE);
		Sleep(keypress_delay_ms);
	}

	void arrowDownUp() {
		keyup(SPECIAL_SCANCODE);
		keyup(ARROW_DOWN_SCANCODE);
		Sleep(keypress_delay_ms);
	}

	void arrowRightUp() {
		keyup(SPECIAL_SCANCODE);
		keyup(ARROW_RIGHT_SCANCODE);
		Sleep(keypress_delay_ms);
	}

	void arrowUpClick() {
		arrowUpDown();
		arrowUpUp();
	}

	void arrowLeftClick() {
		arrowLeftDown();
		arrowLeftUp();
	}

	void arrowDownClick() {
		arrowDownDown();
		arrowDownUp();
	}

	void arrowRightClick() {
		arrowRightDown();
		arrowRightUp();
	}

	void f4KeyDown() {
		keydown(F4_SCANCODE);
	}

	void f4KeyUp() {
		keyup(F4_SCANCODE);
	}

	void f4KeyClick() {
		f4KeyDown();
		f4KeyUp();
	}
}

using namespace WinInterface;