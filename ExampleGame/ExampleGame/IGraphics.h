#ifndef IGRAPHICS_H_DEFINED
#define IGRAPHICS_H_DEFINED

#include "ICamera.h"
#include <Windows.h>
#include <DirectXMath.h>

using namespace DirectX;

typedef struct VERTEX
{
	FLOAT X, Y, Z;
	XMFLOAT4 color;
} VERTEX;

typedef struct MESH_DATA
{
	VERTEX *mVertices;
	UINT *mIndices;
	int mVCount;
	int mICount;

	public:
		MESH_DATA(VERTEX *vertices, UINT *indices, int vCount, int iCount) : mVertices(vertices), mIndices(indices), mVCount(vCount), mICount(iCount) {};
} MESH_DATA;

class IGraphics 
{
	protected:
		ICamera *mCamera;

	public:	
		IGraphics(ICamera *camera) : mCamera(camera) {}

		virtual void updateScene(HWND hWnd, MESH_DATA *bufferData, float angle) = 0;
		virtual void render() = 0;

		inline ICamera *getCamera() { return this->mCamera; }
};

#endif