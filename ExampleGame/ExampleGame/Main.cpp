#include "GraphicsWindow.h"
#include "D3DXGraphics.h"
#include "IGraphics.h"
#include <Windows.h>

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

IGraphics *getGraphicsObject(std::string name)
{
	if (name._Equal("d3dx"))
	{
		return new D3DXGraphics();
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrvInstance, LPSTR lpCmdLine, int nCmdShow) {
	GraphicsWindow *window = new GraphicsWindow(hInstance, "WindowOne", "One", getGraphicsObject("d3dx"));

	// create a triangle using the VERTEX struct
	VERTEX vertices[] =
	{
		{ -0.5f, 0.5f, 0.0f, XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f) },
		{ 0.5f, 0.5, 0.0f, XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f) },
		{ 0.5f, -0.5f, 0.0f, XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f) }
		//{ -0.5f, -0.5f, 0.0f, XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f) }
	};

	MSG msg = {};
	while (GetMessage(&msg, 0, 0, 0)) {
		window->updateScene(vertices, 3);
		window->render();

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, message, wParam, lParam);
}