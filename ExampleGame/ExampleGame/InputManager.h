#pragma once

#include <Windows.h>
#include <map>

class InputManager
{
	static InputManager *mManager;
	std::map<char, bool> keyMap;
	InputManager();
	int mouseX;
	int mouseY;

	public:
		static InputManager *&getInstance();

		void registerRawInput(HWND hWnd);
		void handleInput(WPARAM wParam, LPARAM lParam, UINT state);
		bool getKeyState(const char c);

		inline int getMouseX() { return this->mouseX; }
		inline int getMouseY() { return this->mouseY; }

		inline void setMouseX(int mouseX) { this->mouseX = mouseX; }
		inline void setMouseY(int mouseY) { this->mouseY = mouseY; }
};