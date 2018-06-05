#pragma once

#include <Windows.h>

class AbstractWindow {
	UINT mWidth;
	UINT mHeight;
	const char *mTitle;
	const char *mClassName;
	HWND hWnd;

	bool init(HINSTANCE hInstance);

	static LRESULT CALLBACK staticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	AbstractWindow(HINSTANCE hInstance, UINT width, UINT height, const char *className, const char *title);
	AbstractWindow(HINSTANCE hInstance, const char *className, const char *title);

	inline HWND getHWnd() { return this->hWnd; }
	inline UINT getWidth() { return this->mWidth; }
	inline UINT getHeight() { return this->mHeight; }

	~AbstractWindow();
};