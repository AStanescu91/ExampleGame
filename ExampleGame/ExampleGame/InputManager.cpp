#include "InputManager.h"

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

void InputManager::handleInput(const char c, UINT state)
{
	if (state == WM_KEYDOWN)
	{
		this->keyMap[c] = true;
	}
	else if (state == WM_KEYUP)
	{
		this->keyMap[c] = false;
	}
}

bool InputManager::getKeyState(const char c)
{
	return this->keyMap[c];
}