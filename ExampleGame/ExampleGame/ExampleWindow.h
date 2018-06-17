#pragma once
#include "BaseWindow.h"
#include "BaseGraphics.h";
#include <Windows.h>

class ExampleWindow : public BaseWindow {
	BaseGraphics *mGraphics;

	LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	ExampleWindow(HINSTANCE hInstance, UINT width, UINT height, const char *className, const char *title);
	ExampleWindow(HINSTANCE hInstance, const char *className, const char *title);

	void updateScene(HWND hWnd, MESH_DATA *bufferData, double elapsed);
	void render();

	inline void setGraphics(BaseGraphics *&graphics) { this->mGraphics = graphics; }

	~ExampleWindow();
};