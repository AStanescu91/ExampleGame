#include "Window.h"
#include "D3DXGraphics.h"
#include <Windows.h>

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrvInstance, LPSTR lpCmdLine, int nCmdShow) {
	Window *window = new Window(hInstance, "WindowOne", "One");

	D3DXGraphics *graphics = new D3DXGraphics(window->GetHWnd());

	MSG msg = {};
	while (GetMessage(&msg, 0, 0, 0)) {
		graphics->Render();

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, message, wParam, lParam);
}