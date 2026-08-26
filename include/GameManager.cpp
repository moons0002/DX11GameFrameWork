#include "GameManager.h"

#include "Device.h"
#include "resource.h"
#include "Share/Timer.h"
#include "Shader/ShaderManager.h"
#include "Asset/AssetManager.h"
#include "Scene/SceneManager.h"
#include "ProfileManager.h"
#include "Render/RenderManager.h"
#include "Render/RenderState.h"
#include "Render/RenderStateManager.h"


#include "Shader/ConstantBuffer/TransformCBuffer.h"
#include "Math/Matrix.h"

TCHAR gRootPath[MAX_PATH];
char gRootPathMultibyte[MAX_PATH];

bool CGameManager::mLoop = true;

bool CGameManager::Init(HINSTANCE hInst)
{
	mhInst = hInst;

    lstrcpy(mClassName, L"ClassName");
    lstrcpy(mTitleName, L"TitleName");

    RegisterWindowClass();

    if (!Create()) return false;

    mhDC = GetDC(mhWnd);

    if (!CDevice::GetInstance().Init(mhWnd, WINDOW_WIDTH, WINDOW_HEIGHT, true))
    {
        return false;
    }
    if (!CShaderManager::GetInstance().Init())
    {
        return false;
    }
    if (!CRenderManager::GetInstance().Init())
    {
        return false;
    }
    if (!CAssetManager::GetInstance().Init())
    {
        return false;
    }
    if (!CSceneManager::GetInstance().Init())
    {
        return false;
    }
    if (!CProfileManager::GetInstance().Init())
    {
        return false;
    }
    if (!CTimer::Init())
    {
        return false;
    }

    return true;
}

int CGameManager::Run()
{
    MSG msg = {};

    while (mLoop) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Logic();
        }
    }

    return (int)msg.wParam;
}

void CGameManager::SwitchPause()
{
    mIsPause = !mIsPause;
}

float CGameManager::GetDeltaTime()
{
    return mDeltaTime;
}

void CGameManager::Logic()
{
    float DeltaTime = CTimer::Update();
    mDeltaTime = DeltaTime;

    if (mIsPause) DeltaTime = 0.f;

    Input(DeltaTime);
	Update(DeltaTime);
	Collision(DeltaTime);
	Render(DeltaTime);

    CAssetManager::GetInstance().GetSoundManager()->Update();
}

void CGameManager::Input(float DeltaTime)
{
    CSceneManager::GetInstance().Input(DeltaTime);
}

void CGameManager::Update(float DeltaTime)
{
    CSceneManager::GetInstance().Update(DeltaTime);
}

void CGameManager::Collision(float DeltaTime)
{
    CSceneManager::GetInstance().Collision(DeltaTime);
}

void CGameManager::Render(float DeltaTime)
{
    CDevice::GetInstance().ClearBackBuffer(mClearColor);
    CDevice::GetInstance().ClearDepthStencil(1.f, 0);
    CDevice::GetInstance().SetTarget();

    std::shared_ptr<CRenderState> AlphaBlend = CRenderManager::GetInstance().GetStateManager()->FindState("AlphaBlend");

    if (AlphaBlend)
    {
        AlphaBlend->SetState();
    }

    CSceneManager::GetInstance().Render(DeltaTime);

    if (AlphaBlend)
    {
        AlphaBlend->ResetState();
    }

    CDevice::GetInstance().Render();
}

ATOM CGameManager::RegisterWindowClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;

    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;

    wcex.hInstance = mhInst;

    wcex.hIcon = LoadIcon(mhInst, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    wcex.lpszMenuName = 0;
    wcex.lpszClassName = mClassName;

    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

bool CGameManager::Create()
{
	mhWnd = CreateWindowW(mClassName, mTitleName, WS_OVERLAPPEDWINDOW,
		0, 0, 0, 0, nullptr, nullptr, mhInst, nullptr);

    if (!mhWnd)
    {
        return false;
    }

    RECT WindowRC = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    AdjustWindowRect(&WindowRC, WS_OVERLAPPEDWINDOW, FALSE);
    SetWindowPos(mhWnd, HWND_TOPMOST, 0, 0, WindowRC.right - WindowRC.left,
        WindowRC.bottom - WindowRC.top, SWP_NOMOVE | SWP_NOZORDER);

    ShowWindow(mhWnd, SW_SHOW);
    UpdateWindow(mhWnd);

    return true;
}

LRESULT CGameManager::WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        mLoop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
	ReleaseDC(mhWnd, mhDC);
}
