#pragma once

#include "../../GameInfo.h"

class UICamera
{
public:
	UICamera();
	virtual ~UICamera();

protected:
	FMatrix mmatView;
	FMatrix mmatProj;

	float mWidth = 256.f;
	float mHeight = 192.f;

public:
	const FMatrix& GetViewMatrix() const
	{
		return mmatView;
	}
	const FMatrix& GetProjMatrix() const
	{
		return mmatProj;
	}

protected:
	void SetViewResolution(float Width, float Height)
	{
		mWidth = Width; mHeight = Height;
	}

public:
	bool Init();
};

