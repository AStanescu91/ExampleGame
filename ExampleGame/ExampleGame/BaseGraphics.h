#ifndef BaseGraphics_H_DEFINED
#define BaseGraphics_H_DEFINED

#include "BaseCamera.h"
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

class BaseGraphics 
{
	protected:
		BaseCamera *mCamera;

	public:	
		BaseGraphics() {}

		virtual void updateScene() = 0;
		virtual void render(MESH_DATA *&bufferData, float lag) = 0;

		inline BaseCamera *getCamera() { return this->mCamera; }
		inline void setCamera(BaseCamera *camera) { this->mCamera = camera; }
};

#endif