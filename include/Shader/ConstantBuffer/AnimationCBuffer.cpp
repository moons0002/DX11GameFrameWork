#include "AnimationCBuffer.h"

CAnimationCBuffer::CAnimationCBuffer()
{
}

CAnimationCBuffer::~CAnimationCBuffer()
{
}

bool CAnimationCBuffer::Init()
{
	SetConstantBuffer("Animation");

	return true;
}

void CAnimationCBuffer::UpdateBuffer()
{
	mBuffer->Update(&mData);
}

CAnimationCBuffer* CAnimationCBuffer::Clone()
{
	return new CAnimationCBuffer(*this);
}

void CAnimationCBuffer::SetSize(FVector2D Size)
{
	mData.Size = Size;
}

void CAnimationCBuffer::SetPadding(FVector2D Padding)
{
	mData.Padding = Padding;
}

void CAnimationCBuffer::SetHorizontalFlip(bool HorizontalFlip)
{
	mData.HorizontalFlip = HorizontalFlip ? 1 : 0;
}

void CAnimationCBuffer::SetVerticalFlip(bool VerticalFlip)
{
	mData.VerticalFlip = VerticalFlip ? 1 : 0;
}
