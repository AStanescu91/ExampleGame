#ifndef WINDOW_H_DEFINED
#define WINDOW_H_DEFINED

#include <Windows.h>

class Window {
	UINT mWidth;
	UINT mHeight;
	const char *mTitle;
	HWND hWnd;

	bool init(HINSTANCE hInstance);

	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	public:
		Window(HINSTANCE hInstance, UINT width, UINT height, const char *title);
		Window(HINSTANCE hInstance, const char *title) : Window(hInstance, 800, 600, title) {}
		Window(HINSTANCE hInstance) : Window(hInstance, 800, 600, "Untitled") {};

		LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		inline HWND getHWnd() { return this->hWnd; }

		~Window();
};

#endif
