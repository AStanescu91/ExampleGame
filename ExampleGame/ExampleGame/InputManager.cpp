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

void InputManager::handleInput(WPARAM wParam, LPARAM lParam, UINT state)
{
	if (state == WM_KEYDOWN)
	{
		this->keyMap[wParam] = true;
	}
	else if (state == WM_KEYUP)
	{
		this->keyMap[wParam] = false;
	}
	else if (state == WM_MOUSEMOVE)
	{
		this->mouseX = GET_X_LPARAM(lParam);
		this->mouseY = GET_Y_LPARAM(lParam);
	}
}

bool InputManager::getKeyState(const char c)
{
	return this->keyMap[c];
}