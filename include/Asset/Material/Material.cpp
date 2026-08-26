#include "Material.h"

#include "../../Scene/Scene.h"
#include "../Texture/Texture.h"
#include "../../Shader/ShaderManager.h"
#include "../AssetManager.h"
#include "../../Shader/MaterialCBuffer.h"
#include "../Texture/TextureManager.h"
#include "../../Device.h"

ID3D11SamplerState* CMaterial::mSampler[ETextureSamplerType::End];

CMaterial::CMaterial()
{
	mCBuffer = new CMaterialCBuffer;
	mCBuffer->Init();
}

CMaterial::CMaterial(const CMaterial& Material)
{
	mCBuffer = new CMaterialCBuffer;
	mCBuffer->Init();

	mPS = Material.mPS;
	mBaseColor = Material.mBaseColor;
	mOpacity = Material.mOpacity;
	mSamplerType = Material.mSamplerType;

	mCBuffer->SetBaseColor(mBaseColor);
	mCBuffer->SetOpacity(mOpacity);
}

CMaterial::~CMaterial()
{
	SAFE_DELETE(mCBuffer);
}

void CMaterial::SetSampler(ETextureSamplerType::Type Type)
{
	D3D11_SAMPLER_DESC Desc = {};

	// MIN : 축소
	// MAG : 확대
	// MIP : MipMap

	switch (Type)
	{
	case ETextureSamplerType::Point:
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		break;
	case ETextureSamplerType::Linear:
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		break;
	case ETextureSamplerType::Anisotropic:
		Desc.Filter = D3D11_FILTER_ANISOTROPIC;
		break;
	}

	/*
	WRAP	: UV 0 ~ 1을 벗어나면 다시 0~ 1 사이로 반복한다. 
	MIRROR	: UV 0 ~ 1을 벗어나면 거울에 비친것처럼 반전되어 반복한다. 
	CLAMP	: UV 0 ~ 1을 벗어나면 가장자리 픽셀 색상으로 고정된다. 
	*/

	Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	// LOD 사용시 필요
	// 우리는 사용안할것이기에 필요없다. 
	Desc.MipLODBias = 0.f;
	Desc.MaxAnisotropy = 1;
	// 샘플링 비교 함수
	Desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	Desc.MinLOD = -FLT_MAX;
	Desc.MaxLOD = FLT_MAX;

	if (FAILED(CDevice::GetInstance().GetDevice()->CreateSamplerState(&Desc, &mSampler[Type])))
	{
		return;
	}
}

void CMaterial::DestroySampler()
{
	for (int i = 0; i < ETextureSamplerType::End; ++i)
	{
		SAFE_RELEASE(mSampler[i]);
	}
}

// 픽셀 쉐이더 
void CMaterial::SetPixelShader(const std::string& Name)
{
	const std::shared_ptr<FMaterialPixelShader> mps = CShaderManager::GetInstance().FindPixelShader(Name);

	if (!mps)
	{
		return;
	}

	mPS = mps->PS;
}

void CMaterial::SetPixelShader(const std::string& Name, const char* EntryName, const TCHAR* FileName)
{
	if (!CShaderManager::GetInstance().LoadPixelShader(Name, EntryName, FileName))
	{
		return;
	}

	const std::shared_ptr<FMaterialPixelShader> mps = CShaderManager::GetInstance().FindPixelShader(Name);
	if (!mps)
	{
		return;
	}

	mPS = mps->PS;
}

void CMaterial::ClearShader()
{
	mPS = nullptr;
}

void CMaterial::SetBaseColor(const FVector4D& Color)
{
	mBaseColor = Color;
	mCBuffer->SetBaseColor(Color);
}

void CMaterial::SetBaseColor(float r, float g, float b, float a)
{
	mBaseColor = FVector4D(r, g, b, a);
	mCBuffer->SetBaseColor(mBaseColor);
}

void CMaterial::SetOpacity(float Opacity)
{
	mOpacity = Opacity;
	mCBuffer->SetOpacity(mOpacity);
}

void CMaterial::AddOpacity(float Opacity)
{
	mOpacity += Opacity;
	if (mOpacity > 1) mOpacity = 1.f;
	if (mOpacity < 0) mOpacity = 0.f;
	mCBuffer->SetOpacity(mOpacity);
}

float CMaterial::GetOpacity()
{
	return mOpacity;
}

void CMaterial::SetSamplerType(ETextureSamplerType::Type SamplerType)
{
	mSamplerType = SamplerType;
}

//그리기전에 해당 머티리얼 셋팅으로 데이터를 넣어준다. 
void CMaterial::SetMaterial()
{
	//상수버퍼 셋팅
	mCBuffer->UpdateBuffer();

	//샘플러 셋팅
	CDevice::GetInstance().GetContext()->PSSetSamplers(0, 1, &mSampler[mSamplerType]);

	//픽셀쉐이더 셋팅
	if (mPS)
	{
		CDevice::GetInstance().GetContext()->PSSetShader(mPS, nullptr, 0);CDevice::GetInstance().GetContext()->PSSetShader(mPS, nullptr, 0);
	}
}


std::shared_ptr<CMaterial> CMaterial::Clone()
{
	return std::make_shared<CMaterial>(*this);
}