#pragma once

#include "../Gameinfo.h"

class CRenderState
{
protected:
	ID3D11DeviceChild* mState = nullptr;
	ID3D11DeviceChild* mPrevState = nullptr;
	ERenderStateType::Type mStateType;

public:
	virtual void SetState() = 0;
	virtual void ResetState() = 0;

	virtual void SetBlendFactor(float r, float g, float b, float a) = 0;
	virtual void SetSampleMaks(UINT Mask) = 0;

	virtual void AddBlendDesc(bool Enable, 
		D3D11_BLEND Src, D3D11_BLEND Dest, D3D11_BLEND_OP BlendOp,
		D3D11_BLEND SrcAlpha, D3D11_BLEND DestAlpha, D3D11_BLEND_OP AlphaOp,
		UINT8 RenderTargetWriteMask) = 0;

	virtual bool CreateState(bool AlphaToCoverageEnable, bool IndependentBlendEnable) = 0;

public:
	CRenderState();
	virtual ~CRenderState();
};

