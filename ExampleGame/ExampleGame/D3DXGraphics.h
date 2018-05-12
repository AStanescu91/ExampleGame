#ifndef D3DXGRAPHICS_H_DEFINED
#define D3DXGRAPHICS_H_DEFINED

#include <DirectXMath.h>
#include <d3d11.h>
#include <vector>

using namespace DirectX;

class D3DXGraphics {
	struct VERTEX 
	{
		FLOAT X, Y, Z;
		XMVECTOR color;
	};

	ID3D11Device *mDev;
	ID3D11DeviceContext *mDevCon;
	IDXGISwapChain *mSwapChain;
	ID3D11RenderTargetView *mBackBuffer;
	ID3D11InputLayout *mLayout;
	ID3D11VertexShader *mVShader;
	ID3D11PixelShader *mPShader;
	ID3D11Buffer *mVBuffer;

	int ReadData(const char *fileName, unsigned char *&buf);

	bool InitD3D(HWND hWnd);
	void RenderFrame();
	void CleanD3D();
	void InitGraphics();
	void InitPipeline();

	public:
		D3DXGraphics(HWND hWnd);

		void Render();

		~D3DXGraphics();
};

#endif
