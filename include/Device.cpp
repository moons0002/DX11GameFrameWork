#include "Device.h"

bool CDevice::Init(HWND hWnd,unsigned int Width,unsigned int Height,bool WindowMode)
{
    mhWnd = hWnd;
    mRS.Width = Width;
    mRS.Height = Height;
    mWindowMode = WindowMode;

    // Create Device
    unsigned int Flag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    Flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL FLevel = D3D_FEATURE_LEVEL_11_0;
    D3D_FEATURE_LEVEL FLevelResult;

    if(FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0,
        Flag, &FLevel, 1, D3D11_SDK_VERSION, &mDevice, &FLevelResult, &mContext)))
    {
        return false;
    }

    // Multi Sampiling
    unsigned int SampleCount = 4;
    unsigned int Check = 0;
    mDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &Check);

    if (Check < 1)
    {
        SampleCount = 1;
    }

    // SwapChain
    DXGI_SWAP_CHAIN_DESC SwapDesc = {};
    
    SwapDesc.BufferDesc.Width = Width;
    SwapDesc.BufferDesc.Height = Height;

    SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    SwapDesc.BufferDesc.RefreshRate.Numerator = 1;
    SwapDesc.BufferDesc.RefreshRate.Denominator = 60;

    SwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    SwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

    SwapDesc.BufferCount = 1;

    SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    SwapDesc.OutputWindow = hWnd;

    SwapDesc.SampleDesc.Quality = 0;
    SwapDesc.SampleDesc.Count = SampleCount;

    SwapDesc.Windowed = WindowMode;

    SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    IDXGIDevice *DXGIDevice = nullptr;
    mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&DXGIDevice);
    
    IDXGIAdapter *Adapter = nullptr;
    DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&Adapter);

    IDXGIFactory *Factory = nullptr;
    Adapter->GetParent(__uuidof(IDXGIFactory), (void**) &Factory);

    if(FAILED(Factory->CreateSwapChain(mDevice, &SwapDesc, &mSwapChain))) {
        SAFE_RELEASE(Factory);
        SAFE_RELEASE(Adapter);
        SAFE_RELEASE(DXGIDevice);
        return false;
    }

    SAFE_RELEASE(Factory);
    SAFE_RELEASE(Adapter);
    SAFE_RELEASE(DXGIDevice);

    // Back Buffer
    ID3D11Texture2D *BackBuffer = nullptr;

    if(FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer))) {
        SAFE_RELEASE(BackBuffer);
        return false;
    }
    if(FAILED(mDevice->CreateRenderTargetView(BackBuffer, nullptr, &mTargetView))) {
        SAFE_RELEASE(BackBuffer);
        return false;
    }

    SAFE_RELEASE(BackBuffer);

    // DepthStencil Buffer
    D3D11_TEXTURE2D_DESC DepthDesc = {};

    DepthDesc.Width = Width;
    DepthDesc.Height = Height;
    DepthDesc.ArraySize = 1;
    
    DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    DepthDesc.Usage = D3D11_USAGE_DEFAULT;

    DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    DepthDesc.SampleDesc.Count = SampleCount;
    DepthDesc.SampleDesc.Quality = 0;
    DepthDesc.MipLevels = 1;

    ID3D11Texture2D *DepthBuffer = nullptr;

    if(FAILED(mDevice->CreateTexture2D(&DepthDesc, nullptr, &DepthBuffer))) {
        SAFE_RELEASE(DepthBuffer);
        return false;
    }
    if(FAILED(mDevice->CreateDepthStencilView(DepthBuffer, nullptr, &mDepthView))) {
        SAFE_RELEASE(DepthBuffer);
        return false;
    }

    SAFE_RELEASE(DepthBuffer);

    // ViewPort
    VP_FULL.Width = (float)Width;
    VP_FULL.Height = (float)Height;
    VP_FULL.MaxDepth = 1.f;

    VP_TOP.Width = (float)Width;
    VP_TOP.Height = (float)Height / 2.f;
    VP_TOP.MaxDepth = 1.f;

    VP_BOTTOM.Width = (float)Width;
    VP_BOTTOM.Height = (float)Height / 2.f;
    VP_BOTTOM.MaxDepth = 1.f;

    VP_BOTTOM.TopLeftY = (float)Height / 2.f;

    mContext->RSSetViewports(1, &VP_TOP);

    return true;
}

void CDevice::ClearBackBuffer(float ClearColor[4])
{
    mContext->ClearRenderTargetView(mTargetView, ClearColor);
}

void CDevice::ClearDepthStencil(float Depth,unsigned char Stencil)
{
    mContext->ClearDepthStencilView(mDepthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, Depth, Stencil);
}

void CDevice::SetTarget()
{
    mContext->OMSetRenderTargets(1, &mTargetView, mDepthView);
}

void CDevice::Render()
{
    mSwapChain->Present(1,0);
}

void CDevice::UseFullScreen()
{
    mContext->RSSetViewports(1, &VP_FULL);
}

void CDevice::UseTopScreen()
{
    mContext->RSSetViewports(1, &VP_TOP);
}

void CDevice::UseBottomScreen()
{
    mContext->RSSetViewports(1, &VP_BOTTOM);
}

CDevice::CDevice()
{
}

CDevice::~CDevice()
{
    SAFE_RELEASE(mSwapChain);
    SAFE_RELEASE(mTargetView);
    SAFE_RELEASE(mDepthView);

    if (mContext)
    {
        mContext->ClearState();
    }

    SAFE_RELEASE(mContext);
    SAFE_RELEASE(mDevice);
}
