#include "Camera.h"

#include "../../GameInfo.h"
#include "../Scene.h"

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
	SAFE_DELETE(mPos);
	SAFE_DELETE(mRot);
}

void CCamera::SetProjectionType(ECameraProjectionType Type)
{
	mProjType = Type;

	switch (mProjType)
	{
	case ECameraProjectionType::Perspective:
		mmatProj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(mViewAngle), mWidth / mHeight, 0.5, mViewDistance);
		break;
	case ECameraProjectionType::Ortho:
		mmatProj = DirectX::XMMatrixOrthographicOffCenterLH(mWidth / -2.f, mWidth / 2.f, mHeight / -2.f, mHeight / 2.f, 0, mViewDistance);
		break;
	default:
		break;
	}
}

bool CCamera::Init()
{
	SetProjectionType(mProjType);
	return true;
}

void CCamera::PostUpdate()
{
	SizeView = *mPos;

	FVector2D Size = mScene.lock()->GetSize();

	if (SizeView.x - (mWidth / 2.f) < -(Size.x / 2.f))
		SizeView.x = -(Size.x / 2.f) + (mWidth / 2.f);
	if ((Size.x / 2.f) < SizeView.x + (mWidth / 2.f))
		SizeView.x = (Size.x / 2.f) - (mWidth / 2.f);

	if (SizeView.y - (mHeight / 2.f) < -(Size.y / 2.f))
		SizeView.y = -(Size.y / 2.f) + (mHeight / 2.f);
	if ((Size.y / 2.f) < SizeView.y + (mHeight / 2.f))
		SizeView.y = (Size.y / 2.f) - (mHeight / 2.f);

	FMatrix matRot;
	FVector3D forward(0.f, 0.f, 1.f);
	FVector3D up(0.f, 1.f, 0.f);
	FVector3D eye = (SizeView);

	matRot.Rotation(*mRot);
	forward = forward.TransformNormal(matRot);
	up = up.TransformNormal(matRot);

	mmatView = DirectX::XMMatrixLookAtLH(eye.Convert(), (eye+forward).Convert(), up.Convert());
}