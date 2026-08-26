#pragma once

#include "GameInfo.h"

class CGameManager
{
private:
	HINSTANCE mhInst = 0;
	HWND mhWnd = 0;
	HDC mhDC = 0;
	TCHAR mClassName[256] = {};
	TCHAR mTitleName[256] = {};

	float mClearColor[4] = {1.f, 1.f, 1.f, 1.f};
	static bool mLoop;

	bool mIsPause = false;

	float mDeltaTime = 0.f;

public:
	bool Init(HINSTANCE hInst);
	int Run();

	void SwitchPause();

	float GetDeltaTime();

private:
	void Logic();

	void Input(float DeltaTime);
	void Update(float DeltaTime);
	void Collision(float DeltaTime);
	void Render(float DeltaTime);

private:
	ATOM RegisterWindowClass();
	bool Create();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	HINSTANCE GetWindowInstance() const
	{
		return mhInst;
	}
	HWND GetWindowHandle()
	{
		return mhWnd;
	}

private:
	CGameManager();
	~CGameManager();
	CGameManager(const CGameManager&) = delete;
	void operator=(const CGameManager&) = delete;

public:
	static CGameManager &GetInstance() {
		static CGameManager inst;
		return inst;
	}
};