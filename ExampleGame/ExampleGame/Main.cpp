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

	MSG msg = {};
	while (GetMessage(&msg, 0, 0, 0)) {
		window->render();

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, message, wParam, lParam);
}