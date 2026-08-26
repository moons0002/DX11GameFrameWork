#pragma once

#include "../GameInfo.h"

class CTimer
{
private:
	static LARGE_INTEGER mSecond;
	static LARGE_INTEGER mTime;
	static float mDeltaTime;

public:
	static bool Init();
	static float Update();

public:
	static float GetDeltaTIme()
	{
		return mDeltaTime;
	}

public:
	CTimer();
	CTimer(const CTimer & Obj);
	CTimer(CTimer && Obj) noexcept;
	~CTimer();
};