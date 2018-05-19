#include "D3DXGraphics.h"
#include "Utils.h"
#include <DirectXMath.h>
#include <vector>
#include <fstream>
#include <memory>
#include <filesystem>

using namespace DirectX;
using namespace std;

D3DXGraphics::D3DXGraphics() 
{
	this->mICount = 0;
}

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

	if (!initShaders())
	{
		return false;
	}

	initConstantBuffer();

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

void D3DXGraphics::updateBuffers(MESH_DATA *bufferData)
{
	mBufferData = bufferData;
	if (this->mVBuffer != 0)
		this->mVBuffer->Release();

	D3D11_BUFFER_DESC vBufferDesc = {};
	vBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vBufferDesc.ByteWidth = sizeof(VERTEX) * bufferData->mVCount;
	vBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// Define the resource data.
	D3D11_SUBRESOURCE_DATA vInitData = {};
	vInitData.pSysMem = bufferData->mVertices;
	vInitData.SysMemPitch = 0;
	vInitData.SysMemSlicePitch = 0;

	mDev->CreateBuffer(&vBufferDesc, &vInitData, &mVBuffer);

	if (this->mIBuffer != 0)
		this->mIBuffer->Release();

	// Fill in a buffer description.
	D3D11_BUFFER_DESC iBufferDesc;
	iBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	iBufferDesc.ByteWidth = sizeof(UINT) * bufferData->mICount;
	iBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	iBufferDesc.CPUAccessFlags = 0;
	iBufferDesc.MiscFlags = 0;

	// Define the resource data.
	D3D11_SUBRESOURCE_DATA iInitData;
	iInitData.pSysMem = bufferData->mIndices;
	iInitData.SysMemPitch = 0;
	iInitData.SysMemSlicePitch = 0;

	// Create the buffer with the device.
	mDev->CreateBuffer(&iBufferDesc, &iInitData, &mIBuffer);
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

void D3DXGraphics::initConstantBuffer()
{
	// Fill in a buffer description.
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(VS_CONSTANT_BUFFER);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	// Create the buffer.
	mDev->CreateBuffer(&cbDesc, 0, &mCBuffer);
}

void D3DXGraphics::updateConstantBuffer(VS_CONSTANT_BUFFER vsConstData)
{
	D3D11_MAPPED_SUBRESOURCE ms;
	mDevCon->Map(mCBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, &vsConstData, sizeof(VS_CONSTANT_BUFFER));
	mDevCon->Unmap(mCBuffer, NULL);
}

//Instead of vbuffer, ibuffer, we pass in list of objects and their state
void D3DXGraphics::updateScene(MESH_DATA *bufferData, float angle)
{
	RECT rect = {};
	GetClientRect(this->hWnd, &rect);

	float width = rect.right - rect.left;
	float height = rect.bottom - rect.top;

	XMMATRIX rotate = XMMatrixRotationY(angle);
	XMMATRIX translate = XMMatrixTranslation(0.0f, 0.0f, 10.0f);

	XMMATRIX viewProj = XMMatrixPerspectiveFovLH(70.0f, width / height, 1.0f, 100.0f);
	XMMATRIX world = rotate * translate;
	XMMATRIX wvpMatrix = XMMatrixTranspose(world * viewProj);

	VS_CONSTANT_BUFFER vsConstData = {};
	XMStoreFloat4x4(&vsConstData.worldViewProj, wvpMatrix);
	
	if (bufferData != this->mBufferData)
		this->updateBuffers(bufferData);

	this->updateConstantBuffer(vsConstData);
	this->mICount = bufferData->mICount;
}

void D3DXGraphics::render() 
{
	// clear the back buffer to a deep blue
	mDevCon->ClearRenderTargetView(mBackBuffer, new float[4] { 0.0f, 0.2f, 0.4f, 1.0f } );

	// select which vertex buffer to display
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	mDevCon->IASetVertexBuffers(0, 1, &mVBuffer, &stride, &offset);
	mDevCon->IASetIndexBuffer(mIBuffer, DXGI_FORMAT_R32_UINT, 0);
	mDevCon->VSSetConstantBuffers(0, 1, &mCBuffer);

	// select which primtive type we are using
	mDevCon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw the vertex buffer to the back buffer
	mDevCon->DrawIndexed(this->mICount, 0, 0);

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