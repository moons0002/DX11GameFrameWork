#include "Tile.h"

#include "../Component/TransformComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "Scene.h"
#include "../Component/AnimationComponent.h"
#include "../Shader/ShaderManager.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Animation/Animaiton.h"
#include "../Asset/Texture/Texture.h"
#include "../Shader/ConstantBuffer/TransformCBuffer.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"

bool CTile::Init()
{
	//mObjectType = ObjectType::Tile;

	// SetTexture("BrontoBurt");

	SetShader("AnimationShader");

	SetMesh("CenterTexRect");

	mAnimation = std::make_shared<CAnimation>();

	mScene = CSceneManager::GetInstance().GetCurrentScene();

	return true;
}

void CTile::SetShader(const std::string & Name)
{
	mShader = CShaderManager::GetInstance().FindShader(Name);
}

void CTile::SetMesh(const std::string & Name)
{
	mMesh = CAssetManager::GetInstance().GetMeshManager()->FindMesh(Name);
}

void CTile::SetTexture(const std::string& TextureName)
{
	mTexture = CAssetManager::GetInstance().GetTextureManager()->FindTexture(TextureName);
}

void CTile::AddAnimation(const std::string& AnimationName, FVector2D Start,FVector2D Size, FVector2D Padding, int Col, int Row)
{
	auto Ani = mTexture.lock()->GetTexture(AnimationName);
	if (!Ani)
	{
		return;
	}
	mAnimation->SetStart(Start);
	mAnimation->SetSize(Size);
	mAnimation->SetPadding(Padding);
	mAnimation->SetWidth(Ani->Width);
	mAnimation->SetHeight(Ani->Height);
	mAnimation->SetRowCol(Row, Col);
}

void CTile::SetSortingOrder(int Order)
{
	mSortingOrder = Order;
}

int CTile::GetSortingOrder()
{
	return mSortingOrder;
}

void CTile::UpdateData()
{
	for (int i = 0; i < mTileInfo.size(); ++i)
	{
		mTileInfo[i]->matScale.Scaling(mScale);
		mTileInfo[i]->matRot.Rotation(mTileInfo[i]->Rot);
		mTileInfo[i]->matTranslate.Translation(mTileInfo[i]->Index);
	
		mTileInfo[i]->matWorld = mTileInfo[i]->matScale * mTileInfo[i]->matRot * mTileInfo[i]->matTranslate;
	}
}

void CTile::AddTileInfo(FVector2D Index)
{
	std::shared_ptr<FTileInfo> NewTileinfo = std::make_shared<FTileInfo>(); 

	NewTileinfo->Index = Index;

	mTileInfo.push_back(NewTileinfo);
}

void CTile::EraseTileInfo(FVector2D Index)
{
	for (int i = 0; i < mTileInfo.size(); ++i)
	{
		if ((mTileInfo[i]->Index.x == Index.x) && (mTileInfo[i]->Index.y == Index.y))
		{
			mTileInfo.erase(mTileInfo.begin() + i);
			return;
		}
	}
}

void CTile::SetScale(FVector3D Scale)
{
	mScale = Scale;
}

void CTile::Render()
{
	for (int i = 0; i < mTileInfo.size(); ++i)
	{
		mTileInfo[i]->mTransformCBuffer->SetWorldMatrix(mTileInfo[i]->matWorld);
		mTileInfo[i]->mTransformCBuffer->SetViewMatrix(mScene.lock()->GetCamera()->GetViewMatrix());
		mTileInfo[i]->mTransformCBuffer->SetProjMatrix(mScene.lock()->GetCamera()->GetProjMatrix());

		mTileInfo[i]->mTransformCBuffer->UpdateBuffer();

		mShader.lock()->SetShader();

		mAnimationCBuffer->UpdateBuffer();

		int SlotCount = mMesh.lock()->GetSlotCount();

		for (int i = 0; i < SlotCount; ++i)
		{
			mTexture.lock()->SetShader(0, EShaderBufferType::Pixel, mAnimation->GetName());

			mMesh.lock()->Render();
		}
	}
}