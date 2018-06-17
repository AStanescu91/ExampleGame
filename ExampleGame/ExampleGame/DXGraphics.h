#ifndef DXGraphics_H_DEFINED
#define DXGraphics_H_DEFINED

#include "BaseGraphics.h"
#include <DirectXMath.h>
#include <d3d11.h>
#include <vector>

using namespace DirectX;

class DXGraphics : public BaseGraphics {
	struct VS_CONSTANT_BUFFER
	{
		XMFLOAT4X4 worldViewProj;
	};

	MESH_DATA *mBufferData;

	ID3D11Device *mDev;
	ID3D11DeviceContext *mDevCon;
	IDXGISwapChain *mSwapChain;
	ID3D11RenderTargetView *mBackBuffer;
	ID3D11InputLayout *mLayout;
	ID3D11VertexShader *mVShader;
	ID3D11PixelShader *mPShader;
	ID3D11Buffer *mVBuffer;
	ID3D11Buffer *mIBuffer;
	ID3D11Buffer *mCBuffer;
	ID3D11RasterizerState *mRasterizerState;

	int mICount;

	bool initD3D(HWND hWnd);
	bool initDeviceAndSwapChain(HWND hWnd, int width, int height);
	bool initRenderTarget();
	void createInputLayout(unsigned char *vShader, int vShaderSize);
	void updateBuffers(MESH_DATA *bufferData);
	bool initShaders();
	void initConstantBuffer();
	XMMATRIX createWorldViewProj(float angle);
	void updateConstantBuffer(VS_CONSTANT_BUFFER vsConstData);
	D3D11_VIEWPORT getViewport(int width, int height);

	public:
		DXGraphics(HWND hWnd);

		void updateScene(HWND hWnd, MESH_DATA *bufferData, double elapsed);
		void render();

		~DXGraphics();
};

#endif
