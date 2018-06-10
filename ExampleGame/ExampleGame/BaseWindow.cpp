#include "BaseWindow.h"

BaseWindow::BaseWindow(HINSTANCE hInstance, UINT width, UINT height, const char *className, const char *title) 
{
	this->mTitle = title;
	this->mClassName = className;

	init(hInstance, width, height);
}

BaseWindow::BaseWindow(HINSTANCE hInstance, const char *className, const char *title) : BaseWindow(hInstance, 800, 600, className, title) {}

LRESULT CALLBACK BaseWindow::staticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BaseWindow* pParent;

	// Get pointer to window
	if (message == WM_CREATE)
	{
		pParent = (BaseWindow *)((LPCREATESTRUCT)lParam)->lpCreateParams;
		SetWindowLongPtr(hWnd,GWL_USERDATA, (LONG_PTR)pParent);
	}
	else
	{
		pParent = (BaseWindow *)GetWindowLongPtr(hWnd, GWL_USERDATA);
		if (!pParent) 
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return pParent->wndProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK BaseWindow::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool BaseWindow::init(HINSTANCE hInstance, UINT width, UINT height) {
	WNDCLASS wndClass = {};
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = staticWndProc;
	wndClass.lpszClassName = this->mClassName;
	wndClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	SetWindowLongPtr(this->mHWnd, GWLP_WNDPROC, (LONG_PTR)this);

	if (!RegisterClass(&wndClass)) {
		return false;
	}

	this->mHWnd = CreateWindow(this->mClassName, this->mTitle, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, hInstance, this);
	if (this->mHWnd == NULL) {
		return false;
	}

	GetClientRect(this->mHWnd, &mBounds);

	return true;
}

BaseWindow::~BaseWindow() {
	
}