#pragma once

#include "../../GameInfo.h"
#include "../Asset.h"

#include "DirectXTex.h"

struct FTextureInfo
{
	// 이미지 정보
	DirectX::ScratchImage* Image = nullptr;

	ID3D11ShaderResourceView* SRV = nullptr;

	// 이미지 크기
	unsigned int Width = 0;
	unsigned int Height = 0;

	// 파일 경로
	TCHAR FileName[MAX_PATH] = {};

	~FTextureInfo()
	{
		SAFE_DELETE(Image);
		SAFE_RELEASE(SRV);
	}
};

class CTexture : public CAsset
{
public:
	CTexture();
	~CTexture();

private:
	std::map<std::string, FTextureInfo*> mTextureList;

public:
	const FTextureInfo* GetTexture(const std::string& Name)
	{
		return mTextureList.find(Name)->second;
	}

	int GetTextureCount() const
	{
		return (int)mTextureList.size();
	}

public:
	bool LoadTexture(const std::string TextureInfoName, const TCHAR* FileName);
	bool LoadTextureFullPath(const std::string TextureInfoName, const TCHAR* FullPath);

public:
	void SetShader(int Register, int ShaderBufferType, const std::string& Name);
	void ResetShader(int Register, int ShaderBufferType);

protected:
	bool CreateResoureceView(const std::string& Name);
};

