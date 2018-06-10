#pragma once

#include <Windows.h>

class BaseWindow {
	const char *mTitle;
	const char *mClassName;

	bool init(HINSTANCE hInstance, UINT width, UINT height);

	static LRESULT CALLBACK staticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
	HWND mHWnd;
	RECT mBounds;

public:
	BaseWindow(HINSTANCE hInstance, UINT width, UINT height, const char *className, const char *title);
	BaseWindow(HINSTANCE hInstance, const char *className, const char *title);

	inline HWND getHWnd() { return this->mHWnd; }
	inline RECT getBounds() { return this->mBounds; }

	~BaseWindow();
};