#pragma once

#include "ConstantBufferData.h"

class TransformCBuffer : public CConstantBufferData
{
public:
	TransformCBuffer();
	~TransformCBuffer();

private:
	FTransformBufferInfo mSavedData;
	FTransformBufferInfo mData;

public:
	bool Init();
	void UpdateBuffer();

	virtual TransformCBuffer* Clone();

public:
	void SetWorldMatrix(const FMatrix& matWorld)
	{
		mSavedData.matWorld = matWorld;
	}
	void SetViewMatrix(const FMatrix& matView)
	{
		mSavedData.matView = matView;
	}
	void SetProjMatrix(const FMatrix& matProj)
	{
		mSavedData.matProj = matProj;
	}
};