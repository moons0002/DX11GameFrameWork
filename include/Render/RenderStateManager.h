#pragma once

#include "../Gameinfo.h"

class CRenderState;

class CRenderStateManager
{
public:
	CRenderStateManager();
	~CRenderStateManager();

private:
	std::unordered_map<std::string, std::shared_ptr<CRenderState>> mRenderStateMap;

public:
	bool Init();

public:
	void SetBlendFactor(const std::string& Name, float r, float g, float b, float a);
	void SetSampleMaks(const std::string& Name, UINT Mask);

	void AddBlendDesc(const std::string& Name, bool Enable,
		D3D11_BLEND Src, D3D11_BLEND Dest, D3D11_BLEND_OP BlendOp,
		D3D11_BLEND SrcAlpha, D3D11_BLEND DestAlpha, D3D11_BLEND_OP AlphaOp,
		UINT8 RenderTargetWriteMask);

	bool CreateBlendState(const std::string& Name, bool AlphaToCoverageEnable, bool IndependentBlendEnable);

	std::shared_ptr<CRenderState> FindState(const std::string& Name);
};

