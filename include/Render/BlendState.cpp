#include "BlendState.h"
#include "../Device.h"

CBlendState::CBlendState()
{
}

CBlendState::~CBlendState()
{
}

void CBlendState::SetBlendFactor(float r, float g, float b, float a)
{
	mBlendFactor[0] = r;
	mBlendFactor[1] = g;
	mBlendFactor[2] = b;
	mBlendFactor[3] = a;
}

void CBlendState::SetSampleMaks(UINT Mask)
{
	mSampleMask = Mask;
}

void CBlendState::AddBlendDesc(bool Enable, D3D11_BLEND Src, D3D11_BLEND Dest, D3D11_BLEND_OP BlendOp,
	D3D11_BLEND SrcAlpha, D3D11_BLEND DestAlpha, D3D11_BLEND_OP AlphaOp, UINT8 RenderTargetWriteMask)
{
	D3D11_RENDER_TARGET_BLEND_DESC Desc = {};

	Desc.BlendEnable = Enable;
	Desc.SrcBlend = Src;
	Desc.DestBlend = Dest;
	Desc.BlendOp = BlendOp;
	Desc.SrcBlendAlpha = SrcAlpha;
	Desc.DestBlendAlpha = DestAlpha;
	Desc.BlendOpAlpha = AlphaOp;

	Desc.RenderTargetWriteMask = RenderTargetWriteMask;

	mDesc.emplace_back(Desc);
}

bool CBlendState::CreateState(bool AlphaToCoverageEnable, bool IndependentBlendEnable)
{
	if (mDesc.empty())
	{
		return false;
	}

	D3D11_BLEND_DESC Desc = {};

	Desc.AlphaToCoverageEnable = AlphaToCoverageEnable;
	Desc.IndependentBlendEnable = IndependentBlendEnable;

	for(int i = 0 ; i < 8; ++i)
	{
		Desc.RenderTarget[i].BlendEnable = false;
		Desc.RenderTarget[i].SrcBlend = D3D11_BLEND_ONE;
		Desc.RenderTarget[i].DestBlend = D3D11_BLEND_ZERO;
		Desc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ZERO;
		Desc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}

	memcpy(Desc.RenderTarget, &mDesc[0], sizeof(D3D11_RENDER_TARGET_BLEND_DESC) * mDesc.size());

	if (FAILED(CDevice::GetInstance().GetDevice()->CreateBlendState(&Desc, (ID3D11BlendState**)&mState)))
	{
		return false;
	}

	return true;
}

void CBlendState::SetState()
{
	CDevice::GetInstance().GetContext()->OMGetBlendState((ID3D11BlendState**)&mPrevState, mPrevBlendFactor, &mPrevSampleMask);

	CDevice::GetInstance().GetContext()->OMSetBlendState((ID3D11BlendState*)mState, mBlendFactor, mSampleMask);
}

void CBlendState::ResetState()
{
	CDevice::GetInstance().GetContext()->OMSetBlendState((ID3D11BlendState*)mPrevState, mPrevBlendFactor, mPrevSampleMask);

	SAFE_RELEASE(mPrevState);
}

