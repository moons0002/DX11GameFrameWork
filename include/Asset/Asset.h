#pragma once

#include "../Share/Object.h"
#include "../GameInfo.h"

class CScene;

enum class EAssetType
{
	Mesh,
	Texture
};

class CAsset: public CObject
{
public:
	CAsset();
	~CAsset();

protected:
	CScene* mScene;

	std::string mName;

	EAssetType mAssetType;

public:
	const std::string& GetName() const
	{
		return mName;
	}

	EAssetType GetAssetType() const
	{
		return mAssetType;
	}

	void SetName(const std::string& Name)
	{
		mName = Name;
	}
};


