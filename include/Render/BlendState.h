#pragma once
#include "RenderState.h"

class CBlendState : public CRenderState
{
public:
	CBlendState();
	virtual ~CBlendState();

protected:
	std::vector<D3D11_RENDER_TARGET_BLEND_DESC> mDesc;

	float mBlendFactor[4] = {};
	float mPrevBlendFactor[4] = {};

	UINT mSampleMask = 0xffffffff;
	UINT mPrevSampleMask = 0;

public:
	void SetBlendFactor(float r, float g, float b, float a);
	void SetSampleMaks(UINT Mask);

	void AddBlendDesc(bool Enable, 
		D3D11_BLEND Src, D3D11_BLEND Dest, D3D11_BLEND_OP BlendOp,
		D3D11_BLEND SrcAlpha, D3D11_BLEND DestAlpha, D3D11_BLEND_OP AlphaOp,
		UINT8 RenderTargetWriteMask);

	bool CreateState(bool AlphaToCoverageEnable, bool IndependentBlendEnable);

public:
	virtual void SetState() override;
	virtual void ResetState() override;
};

