#pragma once

#include "../Object/SceneObject.h"

#include "../GameInfo.h"

class CTexture;
class CAnimationCBuffer;
class CAnimation;
class CScene;

struct FTileInfo
{
	FVector2D Index;

	FVector3D Rot;

	FMatrix matScale;
	FMatrix matRot;
	FMatrix matTranslate;
	FMatrix matWorld;

	std::shared_ptr<class TransformCBuffer> mTransformCBuffer;
};

class CTile
{
public:
	bool Init();

protected:
	// Transform 관련
	std::vector<std::shared_ptr<FTileInfo>> mTileInfo;

	FVector3D mScale = FVector3D(1.f, 1.f, 1.f);

	std::weak_ptr<CScene> mScene;

	// Sprite 관련
	std::weak_ptr<class CShader> mShader;
	std::weak_ptr<class CMesh> mMesh;

	std::weak_ptr<CTexture> mTexture;

	std::shared_ptr<CAnimation> mAnimation;

	int mSortingOrder = 0;

	std::shared_ptr<CAnimationCBuffer> mAnimationCBuffer;

public:
	void SetShader(const std::string& Name);
	void SetMesh(const std::string& Name);

	void SetTexture(const std::string& TextureName);

	void AddAnimation(const std::string& AnimationName, FVector2D Start, FVector2D Size, FVector2D Padding, int Col, int Row);

	void SetSortingOrder(int Order);
	int GetSortingOrder();

public:
	void UpdateData();

	void Render();

	void AddTileInfo(FVector2D Index);
	void EraseTileInfo(FVector2D Index);

	void SetScale(FVector3D Scale);
};

