#pragma once

#include "ICamera.h"

class D3DXPerspectiveCamera : public ICamera
{
	protected:
		float mWidth;
		float mHeight;

		void initActions();

	public:
		D3DXPerspectiveCamera(float width, float height);

		void strafe(int units);
		void fly(int units);
		void update();
};