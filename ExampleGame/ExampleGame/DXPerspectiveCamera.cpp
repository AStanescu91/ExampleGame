#include "DXPerspectiveCamera.h"
#include <string.h>

using namespace DirectX;

DXPerspectiveCamera::DXPerspectiveCamera(float width, float height) : PerspectiveCamera(width, height)
{
	this->mRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	this->mUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	this->mLook = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
}

void DXPerspectiveCamera::strafe(int units)
{
	const float scale = 100.0f;

	XMVECTOR scaledRight = XMVectorScale(this->mRight, units / scale);
	XMVECTOR pos = XMVectorSet(this->mPosition[0], this->mPosition[1], this->mPosition[2], 0.0f);
	pos = XMVectorAdd(pos, scaledRight);

	updatePosition(pos);
}

void DXPerspectiveCamera::fly(int units)
{
	const float scale = 100.0f;

	XMVECTOR scaledUp = XMVectorScale(this->mUp, units / scale);
	XMVECTOR pos = XMVectorSet(this->mPosition[0], this->mPosition[1], this->mPosition[2], 0.0f);
	pos = XMVectorAdd(pos, scaledUp);

	updatePosition(pos);
}

void DXPerspectiveCamera::walk(int units)
{
	const float scale = 100.0f;

	XMVECTOR scaledLook = XMVectorScale(this->mLook, units / scale);
	XMVECTOR pos = XMVectorSet(this->mPosition[0], this->mPosition[1], this->mPosition[2], 0.0f);
	pos = XMVectorAdd(pos, scaledLook);

	updatePosition(pos);
}

void DXPerspectiveCamera::look(float pitch, float yaw, float roll)
{
	XMMATRIX rotMat = XMMatrixRotationAxis(this->mRight, pitch);
	this->mLook = XMVector3TransformNormal(this->mLook, rotMat);

	rotMat = XMMatrixRotationAxis(this->mUp, yaw);
	this->mLook = XMVector3TransformNormal(this->mLook, rotMat);
	
	this->mRight = XMVector3Cross(this->mUp, this->mLook);
	this->mUp = XMVector3Cross(this->mLook, this->mRight);
}

void DXPerspectiveCamera::updatePosition(const DirectX::XMVECTOR &pos)
{
	DirectX::XMFLOAT3 fPos;
	DirectX::XMStoreFloat3(&fPos, pos);

	this->mPosition[0] = fPos.x;
	this->mPosition[1] = fPos.y;
	this->mPosition[2] = fPos.z;
}

void DXPerspectiveCamera::update()
{
	XMVECTOR pos = XMVectorSet(this->mPosition[0], this->mPosition[1], this->mPosition[2], 0.0f);
	XMMATRIX view = XMMatrixLookAtLH(pos, pos + mLook, mUp);
	XMMATRIX proj = view * XMMatrixPerspectiveFovLH(70.0f, this->mWidth / (float)this->mHeight, 1.0f, 1000.0f);

	

	XMFLOAT4X4 tmp;
	XMStoreFloat4x4(&tmp, proj);

	memcpy(this->mViewProjMatrix, &tmp.m[0], sizeof(float) * 16);
}

