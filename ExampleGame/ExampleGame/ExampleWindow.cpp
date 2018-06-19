#include "ExampleWindow.h"
#include "InputManager.h"

ExampleWindow::ExampleWindow(HINSTANCE hInstance, UINT width, UINT height, const char *className, const char *title) 
	: BaseWindow(hInstance, width, height, className, title) 
{
}

ExampleWindow::ExampleWindow(HINSTANCE hInstance, const char *className, const char *title) 
	: ExampleWindow(hInstance, 800, 600, className, title) {}

void ExampleWindow::updateScene()
{
	this->mGraphics->getCamera()->update();
	this->mGraphics->updateScene();
}

void ExampleWindow::render(MESH_DATA *&bufferData, float lag)
{
	this->mGraphics->render(bufferData, lag);
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