#ifndef WINDOW_H_DEFINED
#define WINDOW_H_DEFINED

#include <Windows.h>

class Window {
	UINT mWidth;
	UINT mHeight;
	const char *mTitle;
	const char *mClassName;
	HWND hWnd;

	bool init(HINSTANCE hInstance);

	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	public:
		Window(HINSTANCE hInstance, UINT width, UINT height, const char *className, const char *title);
		Window(HINSTANCE hInstance, const char *className, const char *title) : Window(hInstance, 800, 600, className, title) {}

		LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		inline HWND getHWnd() { return this->hWnd; }

		~Window();
};

#endif
