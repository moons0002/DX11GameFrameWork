#include "RenderStateManager.h"
#include "BlendState.h"
#include "RenderState.h"

CRenderStateManager::CRenderStateManager()
{
}

CRenderStateManager::~CRenderStateManager()
{
}

bool CRenderStateManager::Init()
{
	AddBlendDesc("AlphaBlend", true, D3D11_BLEND_SRC_ALPHA, 
		D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ZERO, D3D11_BLEND_OP_ADD, D3D11_COLOR_WRITE_ENABLE_ALL);

	CreateBlendState("AlphaBlend", true, true);

	return true;
}

void CRenderStateManager::SetBlendFactor(const std::string& Name, float r, float g, float b, float a)
{
	std::shared_ptr<CRenderState> State = FindState(Name);

	if (!State)
	{
		State = std::make_shared<CBlendState>();

		mRenderStateMap.insert(std::make_pair(Name, State));
	}

	State->SetBlendFactor(r, g, b, a);
}

void CRenderStateManager::SetSampleMaks(const std::string& Name, UINT Mask)
{
	std::shared_ptr<CRenderState> State = FindState(Name);

	if (!State)
	{
		State = std::make_shared<CBlendState>();

		mRenderStateMap.insert(std::make_pair(Name, State));
	}

	State->SetSampleMaks(Mask);
}

void CRenderStateManager::AddBlendDesc(const std::string& Name, bool Enable, D3D11_BLEND Src, D3D11_BLEND Dest,
	D3D11_BLEND_OP BlendOp, D3D11_BLEND SrcAlpha, D3D11_BLEND DestAlpha, D3D11_BLEND_OP AlphaOp,
	UINT8 RenderTargetWriteMask)
{
	std::shared_ptr<CRenderState> State = FindState(Name);

	if (!State)
	{
		State = std::make_shared<CBlendState>();

		mRenderStateMap.insert(std::make_pair(Name, State));
	}

	State->AddBlendDesc(Enable,
		Src, Dest, BlendOp,
		SrcAlpha, DestAlpha, AlphaOp,
		RenderTargetWriteMask);
}

bool CRenderStateManager::CreateBlendState(const std::string& Name, bool AlphaToCoverageEnable, bool IndependentBlendEnable)
{
	std::shared_ptr<CRenderState> State = FindState(Name);

	if (!State)
	{
		return false;
	}

	if (!(State->CreateState(AlphaToCoverageEnable, IndependentBlendEnable)))
	{
		return false;
	}

	return true;
}

std::shared_ptr<CRenderState> CRenderStateManager::FindState(const std::string& Name)
{
	auto iter = mRenderStateMap.find(Name);

	if (iter == mRenderStateMap.end())
	{
		return nullptr;
	}

	return iter->second;
}

