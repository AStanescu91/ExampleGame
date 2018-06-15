#include "BaseExampleFactory.h"
#include "DXExampleFactory.h"
#include "ExampleWindow.h"
#include "DXPerspectiveCamera.h"
#include "InputManager.h"
#include <Windows.h>

BaseExampleFactory *&getFactory(std::string name)
{
	BaseExampleFactory *factory = 0;
	if (name.compare("dx") == 0)
	{
		factory = new DXExampleFactory();
	}
	return factory;
}

void processKeyboard(PerspectiveCamera *camera, HWND hWnd)
{
	InputManager *manager = InputManager::getInstance();
	bool quitState = manager->getKeyState(VK_ESCAPE);
	bool aState = manager->getKeyState('A');
	bool dState = manager->getKeyState('D');
	bool wState = manager->getKeyState('W');
	bool sState = manager->getKeyState('S');
	bool xState = manager->getKeyState('X');
	bool spState = manager->getKeyState(VK_SPACE);

	if (quitState)
	{
		PostMessage(hWnd, WM_CLOSE, 0, 0);
	}

	if (aState)
	{
		camera->strafe(-1);
	}

	if (dState)
	{
		camera->strafe(1);
	}

	if (wState)
	{
		camera->walk(1);
	}

	if (sState)
	{
		camera->walk(-1);
	}

	if (xState)
	{
		camera->fly(-1);
	}

	if (spState)
	{
		camera->fly(1);
	}
}

void processMouse(PerspectiveCamera *camera)
{
	InputManager *manager = InputManager::getInstance();

	const float divisor = 1000.0f;
	camera->look(manager->getMouseY() / divisor, manager->getMouseX() / divisor, 0.0f);
	manager->setMouseX(0);
	manager->setMouseY(0);
}

void centerMouse(HWND hWnd)
{
	POINT pt = {};
	RECT rect = {};
	ClientToScreen(hWnd, &pt);
	GetClientRect(hWnd, &rect);
	float centerX = pt.x + (rect.right - rect.left) / 2.0f;
	float centerY = pt.y + (rect.bottom - rect.top) / 2.0f;

	SetCursorPos(centerX, centerY);
}

void processInput(PerspectiveCamera *camera, HWND hWnd)
{
	processKeyboard(camera, hWnd);
	processMouse(camera);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrvInstance, LPSTR lpCmdLine, int nCmdShow) {
	ExampleWindow window = ExampleWindow(hInstance, "WindowOne", "One");
	float windowWidth = window.getBounds().right - window.getBounds().left;
	float windowHeight = window.getBounds().bottom - window.getBounds().top;
	ShowCursor(false);

	BaseExampleFactory *factory = getFactory("dx");

	BaseGraphics *graphics = factory->createGraphics(window.getHWnd());
	window.setGraphics(graphics);

	PerspectiveCamera *camera = factory->createPerspectiveCamera(windowWidth, windowHeight);
	camera->setPosition(0.0f, 0.0f, -10.0f);
	graphics->setCamera(camera);

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

	MESH_DATA *data = new MESH_DATA(vertices, indices, 24, 36);

	MSG msg = {};
	InputManager *manager = InputManager::getInstance();
	manager->registerRawInput(window.getHWnd());

	while (TRUE) {
		processInput(camera, window.getHWnd());
		centerMouse(window.getHWnd());
		angle += 0.001f;

		camera->update();
		window.updateScene(window.getHWnd(), data, angle);
		window.render();

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				return 0;
			}
		}
	}

	return 0;
}