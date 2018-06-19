#pragma once

#include "PerspectiveCamera.h"

class DXPerspectiveCamera : public PerspectiveCamera
{
	float mYaw;
	float mPitch;
	float mRoll;

	DirectX::XMVECTOR mRight;
	DirectX::XMVECTOR mUp;
	DirectX::XMVECTOR mLook;	

	void updatePosition(const DirectX::XMVECTOR &pos);

	public:
		DXPerspectiveCamera(float width, float height);

		void strafe(int units);
		void fly(int units);
		void walk(int units);
		void look(float pitch, float yaw, float roll);

		void update();
};