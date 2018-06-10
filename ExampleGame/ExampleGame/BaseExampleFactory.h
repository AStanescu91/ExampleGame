#ifndef ABSTRACT_EXAMPLE_FACTORY
#define ABSTRACT_EXAMPLE_FACTORY

#include "BaseGraphics.h"
#include "BaseCamera.h"

class BaseExampleFactory
{
	public:
		virtual BaseGraphics *createGraphics(HWND hWnd) = 0;
		virtual BaseCamera *createCamera(UINT width, UINT height) = 0;
};

#endif
