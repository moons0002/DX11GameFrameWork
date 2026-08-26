#pragma once

#include "../../GameInfo.h"

class CScene;

enum class ECameraProjectionType
{
	Perspective,
	Ortho
};

class CCamera
{
	friend class CScene;
public:
	CCamera();
	virtual ~CCamera();

protected:
	ECameraProjectionType mProjType = ECameraProjectionType::Ortho;

	FVector3D* mRot = new FVector3D();
	FVector3D* mPos = new FVector3D();

	FMatrix mmatView;
	FMatrix mmatProj;

	FVector3D SizeView;

	float mViewAngle = 90.f;
	float mWidth = 256.f;
	float mHeight = 192.f;
	float mViewDistance = 1000.f;

	std::weak_ptr<CScene> mScene;

public:
	const FMatrix& GetViewMatrix() const
	{
		return mmatView;
	}
	const FMatrix& GetProjMatrix() const
	{
		return mmatProj;
	}

	FVector3D GetSizeView()
	{
		return SizeView;
	}

public:
	void SetProjectionType(ECameraProjectionType Type);
	void SetViewAngle(float Angle)
	{
		mViewAngle = Angle;
	}
	void SetViewResolution(float Width, float Height)
	{
		mWidth = Width; mHeight = Height;
	}
	void SetViewDistance(float Dist)
	{
		mViewDistance = Dist;
	}

	void SetTarget(FVector3D* Target)
	{
		mPos = Target;
	}

	void SetParentScene(std::shared_ptr<CScene> Scene)
	{
		mScene = Scene;
	}



public:

	virtual bool Init();

	virtual void PostUpdate();
};

