#pragma once
#include "AbstractWindow.h"
#include "IGraphics.h";
#include <Windows.h>

class GraphicsWindow : public AbstractWindow {
	IGraphics *mGraphics;
	UINT mWidth;
	UINT mHeight;

	LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	GraphicsWindow(HINSTANCE hInstance, UINT width, UINT height, const char *className, const char *title);
	GraphicsWindow(HINSTANCE hInstance, const char *className, const char *title);

	void updateScene(HWND hWnd, MESH_DATA *bufferData, float angle);
	void render();

	inline void setGraphics(IGraphics *graphics) { this->mGraphics = graphics; }

	~GraphicsWindow();
};