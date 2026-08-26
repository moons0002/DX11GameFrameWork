#include "TransformCBuffer.h"

TransformCBuffer::TransformCBuffer()
{
}

TransformCBuffer::~TransformCBuffer()
{
}

bool TransformCBuffer::Init()
{
	SetConstantBuffer("Transform");

	return true;
}

void TransformCBuffer::UpdateBuffer()
{

	mData.matWorld = mSavedData.matWorld;
	mData.matView = mSavedData.matView;
	mData.matProj = mSavedData.matProj;

	mData.matWV = mData.matWorld * mData.matView;
	mData.matWVP = mData.matWorld * mData.matView * mData.matProj;

	mData.matWorld.Transpose();
	mData.matView.Transpose();
	mData.matProj.Transpose();
	mData.matWV.Transpose(); 
	mData.matWVP.Transpose();

	mBuffer->Update(&mData);
}

TransformCBuffer* TransformCBuffer::Clone()
{
	return new TransformCBuffer(*this);
}
