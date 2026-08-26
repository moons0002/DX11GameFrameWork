#pragma once

#include "../../GameInfo.h"

class CTexture;
class CAsset;

class CTextureManager
{
public:
	CTextureManager();
	~CTextureManager();

private:
	std::unordered_map<std::string, std::shared_ptr<CTexture>> mTextureMap;

public:
	bool Init();

public:
	bool LoadTexture(const std::string& Name, const TCHAR* FileName, const std::string& LoadTextureName);
	bool LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath, const std::string& LoadTextureName);

	std::shared_ptr<CTexture> FindTexture(const std::string& Name);
	void ReleaseTexture(CAsset* Texture);

public:
	// 간단히 테스트용으로 텍스처뒤에 텍스처를 넣기
	bool PushBackLoadTexture(const std::string& TextureName, const TCHAR* FileName, const std::string& TextureInfoName);
};

