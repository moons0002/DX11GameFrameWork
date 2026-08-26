#pragma once

#include "GameInfo.h"

class CDevice
{
private:
	ID3D11Device *mDevice = nullptr;
	ID3D11DeviceContext *mContext = nullptr;
	IDXGISwapChain *mSwapChain = nullptr;

	HWND mhWnd;

	FResolution mRS;

	bool mWindowMode = true;

	ID3D11RenderTargetView *mTargetView = nullptr;
	ID3D11DepthStencilView *mDepthView = nullptr;

	D3D11_VIEWPORT VP_FULL = {};
	D3D11_VIEWPORT VP_TOP = {};
	D3D11_VIEWPORT VP_BOTTOM = {};

public:
	bool Init(HWND hWnd, unsigned int Width, unsigned int Height, bool WindowMode);

	void ClearBackBuffer(float ClearColor[4]);
	void ClearDepthStencil(float Depth, unsigned char Stencil);

	void SetTarget();
	void Render();

	void UseFullScreen();
	void UseTopScreen();
	void UseBottomScreen();

public:
	ID3D11Device *GetDevice() const
	{
		return mDevice;
	}
	ID3D11DeviceContext *GetContext() const
	{
		return mContext;
	}
	IDXGISwapChain *GetSwapChain() const
	{
		return mSwapChain;
	}
	const FResolution& GetResolution() const
	{
		return mRS;
	}
	bool GetWindowMode() const
	{
		return mWindowMode;
	}

private:
	CDevice();
	~CDevice();
	CDevice(const CDevice&) = delete;
	void operator=(const CDevice&) = delete;

public:
	static CDevice &GetInstance() {
		static CDevice inst;
		return inst;
	}
};

