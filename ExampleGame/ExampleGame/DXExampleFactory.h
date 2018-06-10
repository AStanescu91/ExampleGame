#pragma once

#include "BaseExampleFactory.h"

class DXExampleFactory : public BaseExampleFactory
{
	public:
		BaseGraphics *createGraphics(HWND hWnd);
		BaseCamera *createCamera(UINT width, UINT height);
};