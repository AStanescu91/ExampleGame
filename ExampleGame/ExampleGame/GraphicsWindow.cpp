#include "GraphicsWindow.h"

GraphicsWindow::GraphicsWindow(HINSTANCE hInstance, UINT width, UINT height, const char *className, const char *title, IGraphics *graphics) 
	: AbstractWindow(hInstance, width, height, className, title) 
{
	this->graphics = graphics;
	this->graphics->setHWnd(this->getHWnd());
}

GraphicsWindow::GraphicsWindow(HINSTANCE hInstance, const char *className, const char *title, IGraphics *graphics) 
	: GraphicsWindow(hInstance, 800, 600, className, title, graphics) {}

void GraphicsWindow::updateScene(MESH_DATA *bufferData, float angle)
{
	this->graphics->updateScene(bufferData, angle);
}

void GraphicsWindow::render()
{
	this->graphics->render();
}

GraphicsWindow::~GraphicsWindow() {}