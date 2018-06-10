#pragma once

#include "BaseCamera.h"

class DXCamera : public BaseCamera
{
	protected:
		float mWidth;
		float mHeight;

	public:
		DXCamera(int width, int height);

		void strafe(int units);
		void fly(int units);
		void update();
};