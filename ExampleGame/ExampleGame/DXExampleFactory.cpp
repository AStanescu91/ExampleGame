#include "DXExampleFactory.h"
#include "ExampleWindow.h"
#include "DXGraphics.h"
#include "DXPerspectiveCamera.h"

BaseGraphics *DXExampleFactory::createGraphics(HWND hWnd)
{
	return new DXGraphics(hWnd);
}

PerspectiveCamera *DXExampleFactory::createPerspectiveCamera(float width, float height)
{
	return new DXPerspectiveCamera(width, height);
}