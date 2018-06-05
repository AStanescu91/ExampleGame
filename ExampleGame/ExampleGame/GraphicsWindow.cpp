#include "GraphicsWindow.h"
#include "InputManager.h"

GraphicsWindow::GraphicsWindow(HINSTANCE hInstance, UINT width, UINT height, const char *className, const char *title) 
	: AbstractWindow(hInstance, width, height, className, title) 
{
}

GraphicsWindow::GraphicsWindow(HINSTANCE hInstance, const char *className, const char *title) 
	: GraphicsWindow(hInstance, 800, 600, className, title) {}

void GraphicsWindow::updateScene(HWND hWnd, MESH_DATA *bufferData, float angle)
{
	this->mGraphics->updateScene(hWnd, bufferData, angle);
}

void GraphicsWindow::render()
{
	this->mGraphics->render();
}

LRESULT CALLBACK GraphicsWindow::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	InputManager *manager = InputManager::getInstance();
	manager->handleInput(wParam, message);	

	return DefWindowProc(hWnd, message, wParam, lParam);
}

GraphicsWindow::~GraphicsWindow() {}