#include "DXPerspectiveCamera.h"
#include <string.h>
#include <Windows.h>
#include <WinBase.h>
#include <string>

using namespace DirectX;

DXPerspectiveCamera::DXPerspectiveCamera(float width, float height) : PerspectiveCamera(width, height), mYaw(3.14 / 2.0f), mPitch(0.0f), mRoll(0.0f)
{
	this->mRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	this->mUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	this->mLook = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
}

void DXPerspectiveCamera::strafe(int units)
{
	const float scale = 10.0f;

	XMVECTOR scaledRight = XMVectorScale(this->mRight, units / scale);
	XMVECTOR pos = XMVectorSet(this->mPosition[0], this->mPosition[1], this->mPosition[2], 0.0f);
	pos = XMVectorAdd(pos, scaledRight);

	updatePosition(pos);
}

void DXPerspectiveCamera::fly(int units)
{
	const float scale = 10.0f;

	XMVECTOR scaledUp = XMVectorScale(this->mUp, units / scale);
	XMVECTOR pos = XMVectorSet(this->mPosition[0], this->mPosition[1], this->mPosition[2], 0.0f);
	pos = XMVectorAdd(pos, scaledUp);

	updatePosition(pos);
}

void DXPerspectiveCamera::walk(int units)
{
	const float scale = 10.0f;

	XMVECTOR scaledLook = XMVectorScale(this->mLook, units / scale);
	XMVECTOR pos = XMVectorSet(this->mPosition[0], this->mPosition[1], this->mPosition[2], 0.0f);
	pos = XMVectorAdd(pos, scaledLook);

	updatePosition(pos);
}

void DXPerspectiveCamera::look(float pitch, float yaw, float roll)
{
	this->mYaw -= yaw;
	this->mPitch -= pitch;
	this->mRoll -= roll;

/*	XMMATRIX rotMat = XMMatrixRotationAxis(this->mUp, yaw);
	this->mLook = XMVector3TransformNormal(this->mLook, rotMat);

	rotMat = XMMatrixRotationAxis(this->mRight, pitch);
	this->mLook = XMVector3Transform(this->mLook, rotMat);
	this->mRight = XMVector3Cross(this->mLook, this->mUp);*/

	float x = cos(this->mPitch) * cos(this->mYaw);
	float y = sin(this->mPitch);
	float z = cos(this->mPitch) * sin(this->mYaw);

	this->mLook = XMVectorSet(x, y, z, 0.0f);
	this->mRight = XMVector3Cross(this->mUp, this->mLook);

	update();
}

void DXPerspectiveCamera::updatePosition(const DirectX::XMVECTOR &pos)
{
	DirectX::XMFLOAT3 fPos;
	DirectX::XMStoreFloat3(&fPos, pos);

	this->mPosition[0] = fPos.x;
	this->mPosition[1] = fPos.y;
	this->mPosition[2] = fPos.z;

	update();
}

void DXPerspectiveCamera::update()
{
	XMVECTOR pos = XMVectorSet(this->mPosition[0], this->mPosition[1], this->mPosition[2], 0.0f);
	XMMATRIX view = XMMatrixLookAtLH(pos, pos + this->mLook, this->mUp);
	XMMATRIX proj = XMMatrixPerspectiveFovLH(70.0f, this->mWidth / this->mHeight, 1.0f, 100.0f);

	XMFLOAT4X4 tmp;
	XMStoreFloat4x4(&tmp, view * proj);

	memcpy(this->mViewProjMatrix, &tmp.m[0], sizeof(float) * 16);
}