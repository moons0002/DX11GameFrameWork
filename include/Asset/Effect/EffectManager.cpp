#include "EffectManager.h"

#include "../AssetManager.h"
#include "../../Shader/ShaderManager.h"
#include "../Material/Material.h"
#include "../Texture/Texture.h"

#include "../../Shader/ConstantBuffer/TransformCBuffer.h"
#include "../../Scene/Scene.h"

CEffectManager::CEffectManager()
{
}

CEffectManager::~CEffectManager()
{
}

void CEffectManager::PlayEffect(std::string AnimationInfoName, float PlayTime, FVector3D Position, std::weak_ptr<CTransformComponent> mTransform)
{
	FEffectData EffectData(AnimationInfoName, PlayTime, Position, mTransform);
	EffectData.mStartTime = Time;

	mEffects.emplace_back(EffectData);
}

void CEffectManager::SetShader(const std::string & Name)
{
	mShader = CShaderManager::GetInstance().FindShader(Name);
}

void CEffectManager::SetShader(std::shared_ptr<CShader> Shader)
{
	mShader = Shader;
}

void CEffectManager::SetMesh(const std::string & Name)
{
	mMesh = CAssetManager::GetInstance().GetMeshManager()->FindMesh(Name);

	mMaterialSlots.clear();
	// 메쉬가 가지고 있는 슬롯을 얻어와 채워준다
	if (mMesh.expired())
	{
		return;
	}
	int SlotCount = mMesh.lock()->GetSlotCount();

	for (int i = 0 ; i < SlotCount; ++i)
	{
		std::shared_ptr<FMeshSlot> Slot = mMesh.lock()->GetSlot(i);
		mMaterialSlots.emplace_back(Slot->Material);
	}
}

void CEffectManager::SetMesh(std::shared_ptr<CMesh> Mesh)
{
	mMesh = Mesh;

	mMaterialSlots.clear();
	// 메쉬가 가지고 있는 슬롯을 얻어와 채워준다
	if (mMesh.expired())
	{
		return;
	}
	int SlotCount = mMesh.lock()->GetSlotCount();

	for (int i = 0; i < SlotCount; ++i)
	{
		std::shared_ptr<FMeshSlot> Slot = mMesh.lock()->GetSlot(i);
		mMaterialSlots.emplace_back(Slot->Material);
	}
}

void CEffectManager::SetMaterial(int SlotIndex, const std::string Name)
{
	std::shared_ptr<CMaterial> Material = nullptr;

	Material = CAssetManager::GetInstance().GetMaterialManager()->FindMaterial(Name);

	if (Material)
	{
		Material = Material->Clone();
	}

	mMaterialSlots[SlotIndex] = Material;
}

void CEffectManager::SetMaterial(int SlotIndex, std::shared_ptr<CMaterial> Material)
{
	mMaterialSlots[SlotIndex] = Material;
}

bool CEffectManager::Init()
{
	SetShader("AnimationShader");
	SetMesh("CenterTexRect");
	SetMaterial(0, "DefaultMaterial");

	mAnimationCBuffer = std::make_shared<CAnimationCBuffer>();
	mAnimationCBuffer->Init();

	mTransformCBuffer = std::make_shared<TransformCBuffer>();
	mTransformCBuffer->Init();

	return true;
}

void CEffectManager::PreUpdate(float DeltaTime)
{
	Time += DeltaTime;
	this->DeltaTime = DeltaTime;
}

void CEffectManager::Render()
{
	mShader.lock()->SetShader();

	auto iter = mEffects.begin();
	auto iterEnd = mEffects.end();

	for (; iter != iterEnd;)
	{
		if (Time - iter->mStartTime > iter->mPlayTime)
		{
			iter = mEffects.erase(iter);
			iterEnd = mEffects.end();
			continue;
		}
		mState = iter->mAnimationInfoName;
		ChangeFrame(iter->Index);

		ChangeNextFrame(DeltaTime);
	
		iter->Index = mAnimations[iter->mAnimationInfoName].second->GetIndex();

		UpdateTransform(iter);

		mAnimationCBuffer->UpdateBuffer();

		int SlotCount = mMesh.lock()->GetSlotCount();

		for (int j = 0; j < SlotCount; ++j)
		{
			if (mMaterialSlots[j])
			{
				mMaterialSlots[j]->SetMaterial();
			}

			CAssetManager::GetInstance().GetTextureManager()->FindTexture(mAnimations[iter->mAnimationInfoName].first)
				->SetShader(0, EShaderBufferType::Pixel, mAnimations[iter->mAnimationInfoName].second->GetTextureInfoName());

			mMesh.lock()->Render();
		}
		++iter;
	}
}

void CEffectManager::UpdateTransform(std::vector<FEffectData>::iterator iter)
{
	FVector2D mAnimationSize = GetAnimationSize();
	FVector2D mPivot = GetPivot();

	FMatrix mmatScale;
	FMatrix mmatRot;
	FMatrix mmatTranslate;

	FMatrix mmatWorld;

	if (!(iter->mTransform.expired()))
	{
		iter->PrevRot = iter->mTransform.lock()->GetWorldRotation();
		iter->PrevPos = iter->mTransform.lock()->GetWorldPosition() + FVector3D(mPivot.x, mPivot.y, 0.f) + iter->mPosition;
		iter->PrevView = iter->mTransform.lock()->GetParentObj().lock()->GetScene().lock()->GetCamera()->GetViewMatrix();
		iter->PrevProj = iter->mTransform.lock()->GetParentObj().lock()->GetScene().lock()->GetCamera()->GetProjMatrix();
	}
	mmatScale.Scaling(FVector3D(mAnimationSize.x, mAnimationSize.y, 1.f));
	mmatRot.Rotation(iter->PrevRot);
	mmatTranslate.Translation(iter->PrevPos);

	mmatWorld = mmatScale * mmatRot * mmatTranslate;

	mTransformCBuffer->SetWorldMatrix(mmatWorld);
	mTransformCBuffer->SetViewMatrix(iter->PrevView);
	mTransformCBuffer->SetProjMatrix(iter->PrevProj);

	mTransformCBuffer->UpdateBuffer();
}

void CEffectManager::ChangeFrame(int FrameIndex)
{
	mAnimationCBuffer->SetPadding(mAnimations[mState].second->GetFrame(FrameIndex));
}

void CEffectManager::ChangeNextFrame(float DeltaTime)
{
	mAnimationCBuffer->SetPadding(mAnimations[mState].second->GetNextFrame(DeltaTime));
}

void CEffectManager::FlipHorizon()
{
	bool Horizon = !mAnimations[mState].second->GetHorizontalFlip();
	bool Vertical = mAnimations[mState].second->GetVerticalFlip();
	SetFlip(Horizon, Vertical);
}

void CEffectManager::FlipVertical()
{
	bool Horizon = mAnimations[mState].second->GetHorizontalFlip();
	bool Vertical = !mAnimations[mState].second->GetVerticalFlip();
	SetFlip(Horizon, Vertical);
}

void CEffectManager::SetSpeed(float Speed)
{
	mAnimations[mState].second->SetSpeed(Speed);
}

void CEffectManager::SetPlayOption(FAnimationPlayOption PlayOption)
{
	mAnimations[mState].second->SetPlayOption(PlayOption);
}

void CEffectManager::SetFlip(bool Horizon,bool Vertical)
{
	mAnimations[mState].second->SetHorizontalFlip(Horizon);
	mAnimations[mState].second->SetVerticalFlip(Vertical);

	mAnimationCBuffer->SetHorizontalFlip(Horizon);
	mAnimationCBuffer->SetVerticalFlip(Vertical);
}

void CEffectManager::SetRepeatIndex(int Index)
{
	mAnimations[mState].second->SetRepeatIndex(Index);
}

void CEffectManager::SetPivot(float x, float y)
{
	mAnimations[mState].second->SetPivot(x, y);
}

FVector2D& CEffectManager::GetAnimationSize()
{
	return (mAnimations[mState].second->GetSize());
}

FVector2D& CEffectManager::GetPivot()
{
	return (mAnimations[mState].second->GetPivot());
}

void CEffectManager::AddAnimation(const std::string& TextureName, const std::string& AnimationInfoName, const std::string& AnimationName,
	FVector2D Start,FVector2D Size, FVector2D Padding, int Col, int Row)
{
	auto Ani = CAssetManager::GetInstance().GetTextureManager()->FindTexture(TextureName)->GetTexture(AnimationInfoName);
	if (!Ani)
	{
		return;
	}
	std::shared_ptr<CAnimation> Animation = std::make_shared<CAnimation>();
	Animation->SetStart(Start);
	Animation->SetSize(Size);
	Animation->SetPadding(Padding);
	Animation->SetWidth(Ani->Width);
	Animation->SetHeight(Ani->Height);
	Animation->SetRowCol(Row, Col);
	Animation->SetTextureInfoName(AnimationInfoName);

	mAnimations.insert(std::make_pair(AnimationName, std::make_pair(TextureName ,Animation)));
}

void CEffectManager::ChangeState(const std::string& State, int FrameIndex)
{
	if (mState .compare(State) == 0) return;
	// 그 이름의 state가 없으면 종료
	if (mAnimations.find(State) == mAnimations.end()) return;
	// 현재 상태 변경
	mState = State;
	// 일부 값 초기화
	mAnimations[State].second->Init();

	SetFlip(false, false);
	// Size라는거는 0~1사이의 비율을 넣는다
	mAnimationCBuffer->SetSize(mAnimations[State].second->GetNormalSize());
	// 그럼 오프셋도 0~1사이의 비율을 
	ChangeFrame(FrameIndex);
}

CEffectManager* CEffectManager::Clone()
{
	return new CEffectManager(*this);
}