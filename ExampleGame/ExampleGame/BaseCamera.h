#pragma once

#include <DirectXMath.h>

class BaseCamera
{
	protected:
		BaseCamera(float width, float height) : mWidth(width), mHeight(height), mPosition(new float[3]), mViewProjMatrix(new float[16]) {}

		float *mPosition;
		float *mViewProjMatrix;

		float mWidth;
		float mHeight;
	
		~BaseCamera()
		{
			delete[] mPosition;
			delete[] mViewProjMatrix;
		}
	public:
		inline float *&getPosition() { return this->mPosition; }
		inline void setPosition(float x, float y, float z) { this->mPosition[0] = x; this->mPosition[1] = y; this->mPosition[2] = z; }
		inline float *&getViewProjMatrix() { return this->mViewProjMatrix; }

		virtual void update() = 0;
};
