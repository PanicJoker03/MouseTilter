// Made by RequestFX#1541
// Tuned by PanicJoker03
#define _USE_MATH_DEFINES
#include <Windows.h>
#include <iostream>
#include <shellscalingapi.h>
#include <cmath>

struct VECTOR2D {
	float x, y;
};

HHOOK hook; // Mouse event hook
static const float TILT_ANGLE = 349.0f; // angle tilt in degrees.

LRESULT WINAPI LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
	MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam; // Contains information about a low-level mouse input event.
	
	if (nCode >= 0) {
		switch (wParam) {

		case WM_MOUSEMOVE: {
			POINT cursorPos;
			POINT hookPos = pMouseStruct->pt;
			//HWND hiWnd = WindowFromPoint(pMouseStruct->pt);
			GetCursorPos(&cursorPos); // get current Mouse Position
			//static POINT lastPos = cursorPos;
			//ScreenToClient(hiWnd, &hookPos);
			// calc the next Mouse Position and invert it
			//if()
			int deltaX = hookPos.x - cursorPos.x;
			int deltaY = hookPos.y - cursorPos.y;
			int nextMousePosX = 0;
			int nextMousePosY = 0;



			//if(deltaX)
			//SetCursorPos(cursorPos.x + deltaX, cursorPos.y + deltaY);
			//lastPos = { cursorPos.x + deltaX, cursorPos.y + deltaY };
			//SetCursorPos(cursorPos.x + (deltaX * 0.001), cursorPos.y + (deltaY * 0.001));
			float deltaAngle = atan2f(deltaY, deltaX);
			static const float TILT_ANGLE_RAD = TILT_ANGLE * (M_PI / 180.0f);
			//do some trigonometric magic
			//vector rotation calculation got by Johan Larsson stack overflow answer
			float cosVal = cosf(TILT_ANGLE_RAD);
			float sinVal = sinf(TILT_ANGLE_RAD);
			//rotate delta
			POINT rotatedPt = {
				cosVal * deltaX - sinVal * deltaY,
				sinVal * deltaX + cosVal * deltaY
			};
			//add rotatedPt to cursorPos
			POINT nextPos = {
				cursorPos.x + rotatedPt.x,
				cursorPos.y + rotatedPt.y
			};
			SetCursorPos(nextPos.x, nextPos.y);

			//SetCursorPos(deltaX, deltaY);
			
			//SetCursorPos(pMouseStruct->pt.x + deltaX * 1, pMouseStruct->pt.y + deltaY * 1);
			//SetCursorPos(cursorPos.x + deltaX * 1, cursorPos.y + deltaY * 1);
			//SetCursorPos(200, 200);
			return -1; // return here to cancel the passed mouse movement
		}
		}
	}
	/* If nCode is less than zero, the hook procedure must pass the message to the CallNextHookEx function
	and should return the value returned by CallNextHookEx. */
	return CallNextHookEx(hook, nCode, wParam, lParam);
}

int main() {
	//pnic03: ... show console to close app, close shortcut is to large.
	//ShowWindow(GetConsoleWindow(), SW_HIDE); 

	//custom screen scaling fix
	HRESULT dpiResult = SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE);

	//valido que función SetProcessDpiAwareness sea exitosa
	if (dpiResult == E_INVALIDARG || dpiResult == E_ACCESSDENIED)
	{
		std::cout << "Failed to initialize dpi awareness!\n";
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	hook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, NULL, 0); // initial hook
	//hook validating
	if (!hook) {
		std::cout << "Failed to initialize Hook!\n";
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	MSG msg = { 0 };

	while (msg.message != WM_QUIT) {
		if (GetMessage(&msg, 0, 0, 0)) {
		//if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//Sleep(1); // im not sure if I should put this sleep in

		// SHIFT+CTRL+ALT+DEL_KEY to exit
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000 && GetAsyncKeyState(VK_CONTROL) & 0x8000 &&
			GetAsyncKeyState(VK_SHIFT) & 0x8000 && GetAsyncKeyState(VK_MENU) & 0x8000) break;
	}

	UnhookWindowsHookEx(hook); // clear our hook instance
	return 0;
}
