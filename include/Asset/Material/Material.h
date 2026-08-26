#pragma once

#include "../../GameInfo.h"
#include "../Asset.h"

class CTexture;
class CMaterialCBuffer;

namespace ETextureSamplerType
{
	enum Type
	{
		Point,
		Linear,
		Anisotropic,
		End
	};
}

class CMaterial : public CAsset
{
public:
	CMaterial();
	CMaterial(const CMaterial& Material);
	~CMaterial();

private:
    static ID3D11SamplerState* mSampler[ETextureSamplerType::End];

public:
    static void SetSampler(ETextureSamplerType::Type Type);
    static void DestroySampler();

protected:
    ID3D11PixelShader* mPS = nullptr;

    FVector4D mBaseColor = {1.0f, 1.0f, 1.0f, 1.f};

    float mOpacity = 1.f;

    CMaterialCBuffer* mCBuffer = nullptr;

    ETextureSamplerType::Type mSamplerType = ETextureSamplerType::Linear;

    // 
    std::string mTextureInfoName;

public:

    // PS
    void SetPixelShader(const std::string& Name);
    void SetPixelShader(const std::string& Name, const char* EntryName, const TCHAR* FileName);
    void ClearShader();

    // Base Color
    void SetBaseColor(const FVector4D& Color);
    void SetBaseColor(float r, float g, float b, float a);

    // Opacity
    void SetOpacity(float Opacity);
    void AddOpacity(float Opacity);
    float GetOpacity();

    // Sampler Type
    void SetSamplerType(ETextureSamplerType::Type SamplerType);

    // Draw 
    void SetMaterial();

    std::shared_ptr<CMaterial> Clone();
};

