#include "D3DXGraphics.h"
#include <DirectXMath.h>
#include <vector>
#include <fstream>
#include <memory>
#include <filesystem>

using namespace DirectX;
using namespace std;

D3DXGraphics::D3DXGraphics(HWND hWnd) {
	InitD3D(hWnd);
}

bool D3DXGraphics::InitD3D(HWND hWnd) 
{
	LPRECT winBounds = new RECT();
	if (!GetWindowRect(hWnd, winBounds)) 
	{
		return false;
	}

	int width = winBounds->bottom - winBounds->top;
	int height = winBounds->right - winBounds->left;

	DXGI_SWAP_CHAIN_DESC scd = {};
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Width = width;
	scd.BufferDesc.Height = height;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 4;
	scd.Windowed = TRUE;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &scd, &mSwapChain, &mDev, NULL, &mDevCon);

	ID3D11Texture2D *pBackBuffer;
	mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pBackBuffer);
	mDev->CreateRenderTargetView(pBackBuffer, NULL, &mBackBuffer);
	pBackBuffer->Release();

	mDevCon->OMSetRenderTargets(1, &mBackBuffer, NULL);

	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;

	mDevCon->RSSetViewports(1, &viewport);

	InitGraphics();
	InitPipeline();

	return true;
}

void D3DXGraphics::InitGraphics()
{
	// create a triangle using the VERTEX struct
	VERTEX OurVertices[] =
	{
		{ 0.0f, 0.5f, 0.0f, XMVectorSet( 1.0f, 0.0f, 0.0f, 1.0f ) },
		{ 0.45f, -0.5, 0.0f, XMVectorSet( 0.0f, 1.0f, 0.0f, 1.0f ) },
		{ -0.45f, -0.5f, 0.0f, XMVectorSet( 0.0f, 0.0f, 1.0f, 1.0f ) }
	};

	// create the vertex buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
	bd.ByteWidth = sizeof(VERTEX) * 3;             // size is the VERTEX struct * 3
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

	mDev->CreateBuffer(&bd, NULL, &mVBuffer);       // create the buffer
												   // copy the vertices into the buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	mDevCon->Map(mVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // map the buffer
	memcpy(ms.pData, OurVertices, sizeof(OurVertices));                 // copy the data
	mDevCon->Unmap(mVBuffer, NULL);                                      // unmap the buffer
}

int D3DXGraphics::ReadData(const char *fileName, unsigned char *&buf) {
	const char *MODE = "rb";
	FILE *pFile = 0;
	fopen_s(&pFile, fileName, MODE);

	fseek(pFile, 0, SEEK_END);
	long fSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	buf = (unsigned char *)malloc(fSize);

	int numRead = 0;
	while (numRead != fSize)
	{
		numRead = fread(&buf[numRead], 1, fSize, pFile);
	}

	fclose(pFile);

	return fSize;
};

void D3DXGraphics::InitPipeline()
{
	// load and compile the two shaders
	
	const char *VSHADERPATH = "C:\\Users\\Alex\\source\\repos\\ExampleGame\\ExampleGame\\Debug\\VShader.cso";
	const char *PSHADERPATH = "C:\\Users\\Alex\\source\\repos\\ExampleGame\\ExampleGame\\Debug\\PShader.cso";

	unsigned char *vShader = 0;
	unsigned char *pShader = 0;

	int vShaderSize = ReadData(VSHADERPATH, vShader);
	int pShaderSize = ReadData(PSHADERPATH, pShader);

	// encapsulate both shaders into shader objects
	mDev->CreateVertexShader((void *)&vShader[0], vShaderSize, NULL, &mVShader);
	mDev->CreatePixelShader((void *)&pShader[0], pShaderSize, NULL, &mPShader);

	// set the shader objects
	mDevCon->VSSetShader(mVShader, 0, 0);
	mDevCon->PSSetShader(mPShader, 0, 0);

	// create the input layout object
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	mDev->CreateInputLayout(ied, 2, vShader, vShaderSize, &mLayout);
	mDevCon->IASetInputLayout(mLayout);
}

void D3DXGraphics::Render() 
{
	// clear the back buffer to a deep blue
	mDevCon->ClearRenderTargetView(mBackBuffer, new float[4] { 0.0f, 0.2f, 0.4f, 1.0f } );

	// select which vertex buffer to display
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	mDevCon->IASetVertexBuffers(0, 1, &mVBuffer, &stride, &offset);

	// select which primtive type we are using
	mDevCon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw the vertex buffer to the back buffer
	mDevCon->Draw(3, 0);

	// switch the back buffer and the front buffer
	mSwapChain->Present(0, 0);
}

D3DXGraphics::~D3DXGraphics() {
	mSwapChain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode

	mLayout->Release();
	mVShader->Release();
	mPShader->Release();
	mVBuffer->Release();
	mSwapChain->Release();
	mBackBuffer->Release();
	mDev->Release();
	mDevCon->Release();
}