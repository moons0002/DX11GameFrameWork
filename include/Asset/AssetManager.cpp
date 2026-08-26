#include "AssetManager.h"

bool CAssetManager::Init() {

	GetModuleFileName(0, gRootPath, MAX_PATH);

	int Length = lstrlen(gRootPath);

	for (int i = Length - 1; i >= 0; --i)
	{
		if (gRootPath[i] == '/' || gRootPath[i] == '\\')
		{
			memset(&gRootPath[i+1], 0, sizeof(TCHAR) * (Length - (i + 1)));
			break;
		}
	}

	Length = WideCharToMultiByte(CP_ACP, 0, gRootPath, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, gRootPath, -1, gRootPathMultibyte, Length, nullptr, nullptr);

	mMaterialManager = std::make_shared<CMaterialManager>();
	if (!mMaterialManager->Init())
	{
		return false;
	}

	mMeshManager = std::make_shared<CMeshManager>();
	if (!mMeshManager->Init())
	{
		return false;
	}

	mTextureManager = std::make_shared<CTextureManager>();
	if (!mTextureManager->Init())
	{
		return false;
	}

	mEffectManager = std::make_shared<CEffectManager>();
	if (!mEffectManager->Init())
	{
		return false;
	}

	mSoundManager = std::make_shared<CSoundManager>();
	if (!mSoundManager->Init())
	{
		return false;
	}

	mMaterialManager->InitAllMaterial();

	return true;
}

void CAssetManager::PreUpdate(float DeltaTime)
{
	mEffectManager->PreUpdate(DeltaTime);
}

void CAssetManager::ReleaseAsset(CAsset* Asset)
{
	switch (Asset->GetAssetType())
	{
	case EAssetType::Mesh:
		mMeshManager->ReleaseMesh(Asset);
		break;
	case EAssetType::Texture:
		mTextureManager->ReleaseTexture(Asset);
		break;
	}
}

CAssetManager::CAssetManager()
{
}

CAssetManager::~CAssetManager()
{
}