#include "Window.h"

Window::Window(HINSTANCE hInstance, UINT width, UINT height, const char *className, const char *title) {
	this->mWidth = width;
	this->mHeight = height;
	this->mTitle = title;
	this->mClassName = className;

	init(hInstance);
}

LRESULT CALLBACK Window::StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	Window* pParent;

	// Get pointer to window
	if (message == WM_CREATE)
	{
		pParent = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)pParent);
	}
	else
	{
		pParent = (Window*)GetWindowLongPtr(hWnd, GWL_USERDATA);
		if (!pParent) return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return pParent->WndProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool Window::init(HINSTANCE hInstance) {
	WNDCLASS wndClass = {};
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = StaticWndProc;
	wndClass.lpszClassName = this->mClassName;
	wndClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)this);

	if (!RegisterClass(&wndClass)) {
		return false;
	}

	this->hWnd = CreateWindow(this->mClassName, this->mTitle, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, this);
	if (this->hWnd == NULL) {
		return false;
	}

	return true;
}

Window::~Window() {
	
}