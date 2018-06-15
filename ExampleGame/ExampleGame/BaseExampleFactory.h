#ifndef ABSTRACT_EXAMPLE_FACTORY
#define ABSTRACT_EXAMPLE_FACTORY

#include "BaseGraphics.h"
#include "PerspectiveCamera.h"

class BaseExampleFactory
{
	public:
		virtual BaseGraphics *createGraphics(HWND hWnd) = 0;
		virtual PerspectiveCamera *createPerspectiveCamera(float width, float height) = 0;
};

#endif
