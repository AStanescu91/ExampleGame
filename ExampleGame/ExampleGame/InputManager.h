#pragma once

#include <Windows.h>
#include <map>

class InputManager
{
	static InputManager *mManager;
	std::map<char, bool> keyMap;
	InputManager();
	float mouseX;
	float mouseY;

	public:
		static InputManager *&getInstance();

		virtual void handleInput(WPARAM wParam, LPARAM lParam, UINT state);
		bool getKeyState(const char c);

		inline float getMouseX() { return this->mouseX; }
		inline float getMouseY() { return this->mouseY; }
};