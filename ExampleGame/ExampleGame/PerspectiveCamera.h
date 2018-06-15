#pragma once

#include "BaseCamera.h"

class PerspectiveCamera : public BaseCamera
{
	protected:
		PerspectiveCamera(float width, float height) : BaseCamera(width, height) {}

	public:
		virtual void fly(int units) = 0;
		virtual void strafe(int units) = 0;
		virtual void walk(int units) = 0;
		virtual void look(float pitch, float yaw, float roll) = 0;
		virtual void update() = 0;
};