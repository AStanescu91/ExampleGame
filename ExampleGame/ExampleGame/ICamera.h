#pragma once

#include <DirectXMath.h>

class ICamera
{
	protected:
		float *mPosition;
		float *mViewProjMatrix;

		virtual void update() = 0;

	public:
		inline float *&getPosition() { return this->mPosition; }
		inline void setPosition(float x, float y, float z) { this->mPosition[0] = x; this->mPosition[1] = y; this->mPosition[2] = z; }
		inline float *&getViewProjMatrix() { return this->mViewProjMatrix; }

		virtual void strafe(int units) = 0;
		virtual void fly(int units) = 0;
};
