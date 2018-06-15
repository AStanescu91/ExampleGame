#pragma once

#include "BaseExampleFactory.h"

class DXExampleFactory : public BaseExampleFactory
{
	public:
		BaseGraphics *createGraphics(HWND hWnd);
		PerspectiveCamera *createPerspectiveCamera(float width, float height);
};