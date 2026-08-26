#include "UICamera.h"

UICamera::UICamera()
{
}

UICamera::~UICamera()
{
}

bool UICamera::Init()
{
	mmatProj = DirectX::XMMatrixOrthographicOffCenterLH(mWidth / -2.f, mWidth / 2.f, mHeight / -2.f, mHeight / 2.f, 0, 1000.f);

	mmatView = DirectX::XMMatrixIdentity();
	
	return true;
}