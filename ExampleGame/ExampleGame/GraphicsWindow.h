#pragma once
#include "AbstractWindow.h"
#include "IGraphics.h";
#include <Windows.h>

class GraphicsWindow : AbstractWindow {
	IGraphics *graphics;

public:
	GraphicsWindow(HINSTANCE hInstance, UINT width, UINT height, const char *className, const char *title, IGraphics *graphics);
	GraphicsWindow(HINSTANCE hInstance, const char *className, const char *title, IGraphics *graphics);

	void updateScene(VERTEX *vertices, UINT *indices, int vCount, int iCount, float angle);
	void render();

	~GraphicsWindow();
};