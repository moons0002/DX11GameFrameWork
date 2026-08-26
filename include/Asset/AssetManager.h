#pragma once

#include "../GameInfo.h"

#include "Mesh/MeshManager.h"
#include "Texture/TextureManager.h"
#include "Material/MaterialManager.h"
#include "Effect/EffectManager.h"
#include "Sound/SoundManager.h"

class CAssetManager
{
public:
	bool Init();

	void PreUpdate(float DeltaTime);

private:
	std::shared_ptr<CMeshManager> mMeshManager = nullptr; 
	std::shared_ptr<CTextureManager> mTextureManager = nullptr;
	std::shared_ptr<CMaterialManager> mMaterialManager = nullptr;
	std::shared_ptr<CEffectManager> mEffectManager = nullptr;
	std::shared_ptr<CSoundManager> mSoundManager = nullptr;

public:
	std::shared_ptr<CMeshManager> GetMeshManager() const
	{
		return mMeshManager;
	}
	std::shared_ptr<CTextureManager> GetTextureManager() const
	{
		return mTextureManager;
	}
	std::shared_ptr<CMaterialManager> GetMaterialManager() const
	{
		return mMaterialManager;
	}
	std::shared_ptr<CEffectManager> GetEffectManager() const
	{
		return mEffectManager;
	}
	std::shared_ptr<CSoundManager> GetSoundManager() const
	{
		return mSoundManager;
	}

	void ReleaseAsset(CAsset* Asset);



private:
	CAssetManager();
	~CAssetManager();

public:
	static CAssetManager &GetInstance() {
		static CAssetManager inst;
		return inst;
	}

};
