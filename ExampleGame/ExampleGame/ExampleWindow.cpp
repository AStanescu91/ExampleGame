#include "ExampleWindow.h"
#include "InputManager.h"

ExampleWindow::ExampleWindow(HINSTANCE hInstance, UINT width, UINT height, const char *className, const char *title) 
	: BaseWindow(hInstance, width, height, className, title) 
{
}

ExampleWindow::ExampleWindow(HINSTANCE hInstance, const char *className, const char *title) 
	: ExampleWindow(hInstance, 800, 600, className, title) {}

void ExampleWindow::updateScene(HWND hWnd, MESH_DATA *bufferData, float angle)
{
	this->mGraphics->updateScene(hWnd, bufferData, angle);
}

void ExampleWindow::render()
{
	this->mGraphics->render();
}

LRESULT CALLBACK ExampleWindow::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_SIZE) 
	{
		GetClientRect(this->mHWnd, &this->mBounds);
	}

	InputManager *manager = InputManager::getInstance();
	manager->handleInput(wParam, lParam, message);

	return DefWindowProc(hWnd, message, wParam, lParam);
}

ExampleWindow::~ExampleWindow() {}