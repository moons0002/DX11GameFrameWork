#include "Timer.h"

LARGE_INTEGER CTimer::mSecond = {};
LARGE_INTEGER CTimer::mTime = {};
float CTimer::mDeltaTime = 0.f;

bool CTimer::Init()
{
    QueryPerformanceFrequency(&mSecond);
    QueryPerformanceCounter(&mTime);

    return true;
}

float CTimer::Update()
{
	LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    
    mDeltaTime = (time.QuadPart - mTime.QuadPart) / (float)mSecond.QuadPart;

    mTime = time;

    return mDeltaTime;
}

CTimer::CTimer()
{
}

CTimer::CTimer(const CTimer & Obj)
{
}

CTimer::CTimer(CTimer && Obj) noexcept
{
}

CTimer::~CTimer()
{
}
