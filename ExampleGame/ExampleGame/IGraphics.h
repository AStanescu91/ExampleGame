#ifndef IGRAPHICS_H_DEFINED
#define IGRAPHICS_H_DEFINED

#include <Windows.h>
#include <DirectXMath.h>

using namespace DirectX;

typedef struct VERTEX
{
	FLOAT X, Y, Z;
	XMVECTOR color;
} VERTEX;

class IGraphics 
{
	public:	
		virtual void updateScene(VERTEX *vertices, UINT *indices, int vCount, int iCount, float angle) = 0;
		virtual void render() = 0;
		virtual void setHWnd(HWND hWnd) = 0;
};

#endif