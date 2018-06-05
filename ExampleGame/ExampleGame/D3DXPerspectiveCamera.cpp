#include "D3DXPerspectiveCamera.h"
#include <string.h>

D3DXPerspectiveCamera::D3DXPerspectiveCamera(float width, float height)
{
	this->mWidth = width;
	this->mHeight = height;

	this->mPosition = new float[3];
	this->mPosition[0] = 0.0f;
	this->mPosition[1] = 0.0f;
	this->mPosition[2] = 0.0f;

	this->mViewProjMatrix = new float[16];

	update();
}

void D3DXPerspectiveCamera::strafe(int units)
{
	
}

void D3DXPerspectiveCamera::fly(int units)
{

}

void D3DXPerspectiveCamera::update()
{
	DirectX::XMMATRIX viewProj = DirectX::XMMatrixPerspectiveFovLH(70.0f, this->mWidth / this->mHeight, 1.0f, 100.0f);
	DirectX::XMFLOAT4X4 tmp;
	DirectX::XMStoreFloat4x4(&tmp, viewProj);

	memcpy(this->mViewProjMatrix, &tmp.m[0], sizeof(float) * 16);
}

