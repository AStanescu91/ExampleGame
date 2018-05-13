#pragma once

#include <Windows.h>

class IGraphics 
{
	public:	
		virtual void render() = 0;
		virtual void setHWnd(HWND hWnd) = 0;

};