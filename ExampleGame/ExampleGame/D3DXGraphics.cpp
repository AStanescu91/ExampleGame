#include "D3DXGraphics.h"
#include "Utils.h"
#include <DirectXMath.h>
#include <vector>
#include <fstream>
#include <memory>
#include <filesystem>

using namespace DirectX;
using namespace std;

D3DXGraphics::D3DXGraphics() {}

bool D3DXGraphics::initD3D(HWND hWnd) 
{
	LPRECT winBounds = new RECT();
	if (!GetWindowRect(hWnd, winBounds)) 
	{
		return false;
	}

	int width = winBounds->bottom - winBounds->top;
	int height = winBounds->right - winBounds->left;

	if (!initDeviceAndSwapChain(width, height))
	{
		return false;
	}

	if (!initRenderTarget())
	{
		return false;
	}

	D3D11_VIEWPORT viewport = getViewport(width, height);
	mDevCon->RSSetViewports(1, &viewport);

	initGraphics();

	if (!initShaders())
	{
		return false;
	}

	return true;
}

bool D3DXGraphics::initDeviceAndSwapChain(int width, int height)
{
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

	HRESULT res = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &scd, &mSwapChain, &mDev, NULL, &mDevCon);
	if (res != S_OK)
	{
		return false;
	}
	return true;
}

bool D3DXGraphics::initRenderTarget()
{
	ID3D11Texture2D *pBackBuffer;
	mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pBackBuffer);
	mDev->CreateRenderTargetView(pBackBuffer, NULL, &mBackBuffer);
	pBackBuffer->Release();

	if (mBackBuffer == 0)
	{
		return false;
	}

	mDevCon->OMSetRenderTargets(1, &mBackBuffer, NULL);
	return true;
}

D3D11_VIEWPORT D3DXGraphics::getViewport(int width, int height)
{
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	return viewport;
}

void D3DXGraphics::initGraphics()
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

bool D3DXGraphics::initShaders()
{
	// load and compile the two shaders
	
	const char *VSHADERPATH = "VShader.cso";
	const char *PSHADERPATH = "PShader.cso";

	unsigned char *vShader = 0;
	unsigned char *pShader = 0;

	int vShaderSize = Utils::readData(VSHADERPATH, vShader);
	int pShaderSize = Utils::readData(PSHADERPATH, pShader);

	if (vShader == 0 || pShader == 0)
		return false;

	// encapsulate both shaders into shader objects
	mDev->CreateVertexShader((void *)&vShader[0], vShaderSize, NULL, &mVShader);
	mDev->CreatePixelShader((void *)&pShader[0], pShaderSize, NULL, &mPShader);

	// set the shader objects
	mDevCon->VSSetShader(mVShader, 0, 0);
	mDevCon->PSSetShader(mPShader, 0, 0);

	createInputLayout(vShader, vShaderSize);

	return true;
}

void D3DXGraphics::createInputLayout(unsigned char *vShader, int vShaderSize)
{
	// create the input layout object
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	this->mDev->CreateInputLayout(ied, 2, vShader, vShaderSize, &mLayout);
	mDevCon->IASetInputLayout(mLayout);
}

void D3DXGraphics::render() 
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

void D3DXGraphics::setHWnd(HWND hWnd)
{
	this->hWnd = hWnd;	
	initD3D(hWnd);
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