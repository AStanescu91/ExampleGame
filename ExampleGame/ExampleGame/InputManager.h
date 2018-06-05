#pragma once

#include <Windows.h>
#include <map>

class InputManager
{
	static InputManager *mManager;
	std::map<char, bool> keyMap;
	InputManager();

	public:
		static InputManager *&getInstance();

		virtual void handleInput(const char c, UINT state);
		bool getKeyState(const char c);
};