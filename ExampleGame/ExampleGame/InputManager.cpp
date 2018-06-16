#include "InputManager.h"
#include <windowsx.h>

InputManager *InputManager::mManager = 0;

InputManager::InputManager()
{
	this->keyMap = std::map<char, bool>();
}

InputManager *&InputManager::getInstance()
{
	if (mManager == 0)
	{
		mManager = new InputManager();
	}
	return mManager;
}

void InputManager::registerRawInput(HWND hWnd)
{
	RAWINPUTDEVICE rid[2];

	rid[0].usUsagePage = 0x01;
	rid[0].usUsage = 0x02;
	rid[0].dwFlags = RIDEV_NOLEGACY | RIDEV_CAPTUREMOUSE;
	rid[0].hwndTarget = hWnd;

	rid[1].usUsagePage = 0x01;
	rid[1].usUsage = 0x06;
	rid[1].dwFlags = RIDEV_NOLEGACY;
	rid[1].hwndTarget = hWnd;

	if (RegisterRawInputDevices(rid, 2, sizeof(RAWINPUTDEVICE)) == FALSE) {
		//registration failed. Call GetLastError for the cause of the error
	}
}

void InputManager::handleInput(WPARAM wParam, LPARAM lParam, UINT state)
{
	if (state == WM_INPUT)
	{
		UINT dwSize;
		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));

		LPBYTE lpb = new BYTE[dwSize];
		if (lpb == NULL)
		{
			return;
		}

		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));

		RAWINPUT *raw = (RAWINPUT *)lpb;
		if (raw->header.dwType == RIM_TYPEKEYBOARD)
		{
			if ((raw->data.keyboard.Flags & RI_KEY_BREAK) == 0)
			{
				this->keyMap[raw->data.keyboard.VKey] = true;
			}
			else
			{
				this->keyMap[raw->data.keyboard.VKey] = false;
			}
		}
		else if (raw->header.dwType == RIM_TYPEMOUSE)
		{
			this->mouseX = raw->data.mouse.lLastX;
			this->mouseY = raw->data.mouse.lLastY;
		}
	}
}

bool InputManager::getKeyState(const char c)
{
	return this->keyMap[c];
}