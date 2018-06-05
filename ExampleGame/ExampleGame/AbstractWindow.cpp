#include "AbstractWindow.h"

AbstractWindow::AbstractWindow(HINSTANCE hInstance, UINT width, UINT height, const char *className, const char *title) 
{
	this->mWidth = width;
	this->mHeight = height;
	this->mTitle = title;
	this->mClassName = className;

	init(hInstance);
}

AbstractWindow::AbstractWindow(HINSTANCE hInstance, const char *className, const char *title) : AbstractWindow(hInstance, 800, 600, className, title) {}

LRESULT CALLBACK AbstractWindow::staticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	AbstractWindow* pParent;

	// Get pointer to window
	if (message == WM_CREATE)
	{
		pParent = (AbstractWindow *)((LPCREATESTRUCT)lParam)->lpCreateParams;
		SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)pParent);
	}
	else
	{
		pParent = (AbstractWindow *)GetWindowLongPtr(hWnd, GWL_USERDATA);
		if (!pParent) 
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return pParent->wndProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK AbstractWindow::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool AbstractWindow::init(HINSTANCE hInstance) {
	WNDCLASS wndClass = {};
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = staticWndProc;
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

	LPRECT bounds = new RECT();
	GetClientRect(this->hWnd, bounds);
	this->mWidth = bounds->right - bounds->left;
	this->mHeight = bounds->bottom - bounds->top;

	return true;
}

AbstractWindow::~AbstractWindow() {
	
}