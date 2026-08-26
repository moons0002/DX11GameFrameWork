#pragma once

#include "ConstantBufferData.h"

class CAnimationCBuffer : public CConstantBufferData
{
public:
	CAnimationCBuffer();
	~CAnimationCBuffer();

private:
	FAnimationCBufferInfo mData;

public:
	bool Init();
	void UpdateBuffer();

	virtual CAnimationCBuffer* Clone();

public:
	void SetSize(FVector2D Size);
	void SetPadding(FVector2D Padding);

	void SetHorizontalFlip(bool HorizontalFlip);
	void SetVerticalFlip(bool VerticalFlip);
};