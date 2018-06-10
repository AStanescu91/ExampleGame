#include "DXExampleFactory.h"
#include "ExampleWindow.h"
#include "DXGraphics.h"
#include "DXCamera.h"

BaseGraphics *DXExampleFactory::createGraphics(HWND hWnd)
{
	return new DXGraphics(hWnd);
}

BaseCamera *DXExampleFactory::createCamera(UINT width, UINT height)
{
	return new DXCamera(width, height);
}