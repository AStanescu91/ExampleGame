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
		//LEFT FACE GREEN
		{ -0.5f, 0.5f, 0.5f, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ -0.5f, 0.5f, -0.5f, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ -0.5f, -0.5f, -0.5f, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ -0.5f, -0.5f, 0.5f, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },

		//TOP FACE BLUE
		{ -0.5f, 0.5f, 0.5f, XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ 0.5f, 0.5f, 0.5f, XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ 0.5f, 0.5f, -0.5f, XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ -0.5f, 0.5f, -0.5f, XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },

		//RIGHT FACE RED
		{ 0.5f, 0.5f, -0.5f, XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ 0.5f, 0.5f, 0.5f, XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ 0.5f, -0.5f, 0.5f, XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ 0.5f, -0.5f, -0.5f, XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },

		//BOTTOM FACE GREEN + BLUE = CYAN
		{ -0.5f, -0.5f, -0.5f, XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ 0.5f, -0.5f, -0.5f, XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ 0.5f, -0.5f, 0.5f, XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ -0.5f, -0.5f, 0.5f, XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },

		//FRONT FACE GREEN + RED = YELLOW
		{ -0.5f, 0.5f, -0.5f, XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ 0.5f, 0.5f, -0.5f, XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ 0.5f, -0.5f, -0.5f, XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ -0.5f, -0.5f, -0.5f, XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },

		//BACK FACE BLUE + RED = MAGENTA
		{ 0.5f, 0.5f, 0.5f, XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ -0.5f, 0.5f, 0.5f, XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ -0.5f, -0.5f, 0.5f, XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ 0.5f, -0.5f, 0.5f, XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) }
	};

	UINT indices[] =
	{
		//LEFT FACE
		0, 1, 2,
		0, 2, 3,

		//TOP FACE
		4, 5, 6,
		4, 6, 7,

		//RIGHT FACE
		8, 9, 10,
		8, 10, 11,

		//BOTTOM FACE
		12, 13, 14,
		12, 14, 15,

		//FRONT FACE
		16, 17, 18,
		16, 18, 19,

		//BACK FACE
		20, 21, 22,
		20, 22, 23
	};

	float angle = 0.0f;

	MSG msg = {};
	while (TRUE) {
		angle += 0.0001f;
		window->updateScene(new MESH_DATA(vertices, indices, 24, 36), angle);
		window->render();

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, message, wParam, lParam);
}