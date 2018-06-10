#include "BaseExampleFactory.h"
#include "DXExampleFactory.h"
#include "ExampleWindow.h"
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrvInstance, LPSTR lpCmdLine, int nCmdShow) {
	ExampleWindow window = ExampleWindow(hInstance, "WindowOne", "One");
	int windowWidth = window.getBounds().right - window.getBounds().left;
	int windowHeight = window.getBounds().bottom - window.getBounds().top;

	BaseExampleFactory *factory = getFactory("dx");

	BaseGraphics *graphics = factory->createGraphics(window.getHWnd());
	window.setGraphics(graphics);

	BaseCamera *camera = factory->createCamera(windowWidth, windowHeight);
	graphics->setCamera(camera);
	camera->setPosition(0.0f, 0.0f, 10.0f);

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

	while (TRUE) {
		bool quitState = manager->getKeyState(VK_ESCAPE);
		bool aState = manager->getKeyState('A');
		bool dState = manager->getKeyState('D');
		bool wState = manager->getKeyState('W');
		bool sState = manager->getKeyState('S');
		bool xState = manager->getKeyState('X');
		bool spState = manager->getKeyState(VK_SPACE);

		float *curPos = camera->getPosition();

		if (quitState)
		{
			PostQuitMessage(0);
		}

		if (aState)
		{
			camera->setPosition(curPos[0] + 0.001f, curPos[1], curPos[2]);
		}

		if (dState)
		{
			camera->setPosition(curPos[0] - 0.001f, curPos[1], curPos[2]);
		}

		if (wState)
		{
			camera->setPosition(curPos[0], curPos[1], curPos[2] - 0.001f);
		}

		if (sState)
		{
			camera->setPosition(curPos[0], curPos[1], curPos[2] + 0.001f);
		}

		if (xState)
		{
			camera->setPosition(curPos[0], curPos[1] + 0.001f, curPos[2]);
		}

		if (spState)
		{
			camera->setPosition(curPos[0], curPos[1] - 0.001f, curPos[2]);
		}

		angle += 0.0001f;

		window.updateScene(window.getHWnd(), data, angle);
		window.render();

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}