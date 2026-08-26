#include "AnimationComponent.h"

#include "../Shader/ShaderManager.h"
#include "../Shader/AnimationShader.h"

#include "../Asset/AssetManager.h"
#include "../Asset/Texture/TextureManager.h"
#include "../Asset/Material/Material.h"
#include "../Asset/Texture/Texture.h"

#include "../Render/RenderManager.h"

#include "../Object/SceneObject.h"
#include "TransformComponent.h"

CAnimationComponent::CAnimationComponent()
{
	mAnimationCBuffer = std::make_shared<CAnimationCBuffer>();
	mAnimationCBuffer->Init();
}

CAnimationComponent::~CAnimationComponent()
{
}

void CAnimationComponent::SetShader(const std::string & Name)
{
	mShader = CShaderManager::GetInstance().FindShader(Name);
}

void CAnimationComponent::SetShader(std::shared_ptr<CShader> Shader)
{
	mShader = Shader;
}

void CAnimationComponent::SetMesh(const std::string & Name)
{
	mMesh = CAssetManager::GetInstance().GetMeshManager()->FindMesh(Name);

	mMaterialSlots.clear();

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

void CAnimationComponent::SetMesh(std::shared_ptr<CMesh> Mesh)
{
	mMesh = Mesh;

	mMaterialSlots.clear();

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

void CAnimationComponent::SetSortingOrder(int Order)
{
	mSortingOrder = Order;
}

int CAnimationComponent::GetSortingOrder()
{
	return mSortingOrder;
}

void CAnimationComponent::SetMaterial(int SlotIndex, const std::string Name)
{
	std::shared_ptr<CMaterial> Material = nullptr;

	Material = CAssetManager::GetInstance().GetMaterialManager()->FindMaterial(Name);

	if (Material)
	{
		Material = Material->Clone();
	}

	mMaterialSlots[SlotIndex] = Material;
}

void CAnimationComponent::SetMaterial(int SlotIndex, std::shared_ptr<CMaterial> Material)
{
	mMaterialSlots[SlotIndex] = Material;
}

void CAnimationComponent::AddTexture(int SlotIndex, const std::string& Name, const TCHAR* FileName, int Register,
	int ShaderBufferType, const std::string& TextureName)
{
	CAssetManager::GetInstance().GetTextureManager()->LoadTexture(Name, FileName, TextureName);
}

void CAnimationComponent::SetBaseColor(int SlotIndex, float r, float g, float b, float a)
{
	mMaterialSlots[SlotIndex]->SetBaseColor(r, g, b, a);
}

void CAnimationComponent::SetOpacity(int SlotIndex, float Opacity)
{
	mMaterialSlots[SlotIndex]->SetOpacity(Opacity);
}

void CAnimationComponent::AddOpacity(int SlotIndex,float Opacity)
{
	mMaterialSlots[SlotIndex]->AddOpacity(Opacity);
}

float CAnimationComponent::GetOpacity(int SlotIndex)
{
	return mMaterialSlots[SlotIndex]->GetOpacity();
}

void CAnimationComponent::SetTexture(const std::string& TextureName)
{
	mTexture = CAssetManager::GetInstance().GetTextureManager()->FindTexture(TextureName);
}

void CAnimationComponent::AddAnimation(const std::string& AnimationName, std::shared_ptr<CAnimation> Animation)
{
	mAnimations.insert(std::make_pair(AnimationName, Animation));
}

void CAnimationComponent::AddAnimation(const std::string& AnimationInfoName, const std::string& AnimationName, FVector2D Start,FVector2D Size, FVector2D Padding, int Col, int Row)
{
	auto Ani = mTexture.lock()->GetTexture(AnimationInfoName);
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

	mAnimations.insert(std::make_pair(AnimationName, Animation));
}

void CAnimationComponent::ChangeState(const std::string& State, int FrameIndex)
{
	// 현재 State와 비교
	if (mState .compare(State) == 0) return;
	// 그 이름의 state가 없으면 종료
	if (mAnimations.find(State) == mAnimations.end()) return;
	// 현재 State 변경
	mState = State;
	// 애니메이션 초기화
	mAnimations[State]->Init();

	SetFlip(false, false);
	
	mAnimationCBuffer->SetSize(mAnimations[State]->GetNormalSize());
	 
	ChangeFrame(FrameIndex);
}

void CAnimationComponent::ChangeFrame(int FrameIndex)
{
	mAnimationCBuffer->SetPadding(mAnimations[mState]->GetFrame(FrameIndex));
}

void CAnimationComponent::ChangeNextFrame(float DeltaTime)
{
	mAnimationCBuffer->SetPadding(mAnimations[mState]->GetNextFrame(DeltaTime));
}

void CAnimationComponent::FlipHorizon()
{
	bool Horizon = !mAnimations[mState]->GetHorizontalFlip();
	bool Vertical = mAnimations[mState]->GetVerticalFlip();
	SetFlip(Horizon, Vertical);
}

void CAnimationComponent::FlipVertical()
{
	bool Horizon = mAnimations[mState]->GetHorizontalFlip();
	bool Vertical = !mAnimations[mState]->GetVerticalFlip();
	SetFlip(Horizon, Vertical);
}

void CAnimationComponent::SetSpeed(float Speed)
{
	mAnimations[mState]->SetSpeed(Speed);
}

void CAnimationComponent::SetPlayOption(FAnimationPlayOption PlayOption)
{
	mAnimations[mState]->SetPlayOption(PlayOption);
}

void CAnimationComponent::SetFlip(bool Horizon,bool Vertical)
{
	mAnimations[mState]->SetHorizontalFlip(Horizon);
	mAnimations[mState]->SetVerticalFlip(Vertical);

	mAnimationCBuffer->SetHorizontalFlip(Horizon);
	mAnimationCBuffer->SetVerticalFlip(Vertical);
}

void CAnimationComponent::SetRepeatIndex(int Index)
{
	mAnimations[mState]->SetRepeatIndex(Index);
}

void CAnimationComponent::SetPivot(float x, float y)
{
	mAnimations[mState]->SetPivot(x, y);
}

FVector2D& CAnimationComponent::GetAnimationSize()
{
	return (mAnimations[mState]->GetSize());
}

FVector2D& CAnimationComponent::GetPivot()
{
	return (mAnimations[mState]->GetPivot());
}

bool CAnimationComponent::Init()
{
	SetShader("AnimationShader");
	SetMesh("CenterTexRect");
	SetMaterial(0, "DefaultMaterial");

	CRenderManager::GetInstance().PushBackRenderList(mParentObj);

	return true;
}

bool CAnimationComponent::Init(const char* FileName)
{
	SetShader("AnimationShader");
	SetMesh("CenterTexRect");
	SetMaterial(0, "DefaultMaterial");

	CRenderManager::GetInstance().PushBackRenderList(mParentObj);

	return true;
}

void CAnimationComponent::PreRender(float DeltaTime)
{
	CSceneComponent::PreRender(DeltaTime);

	ChangeNextFrame(DeltaTime);
}

void CAnimationComponent::Render()
{
	CSceneComponent::Render();

	mShader.lock()->SetShader();

	mParentObj.lock()->FindComponent("Transform").lock()->Render();
	mAnimationCBuffer->UpdateBuffer();

	int SlotCount = mMesh.lock()->GetSlotCount();

	for (int i = 0; i < SlotCount; ++i)
	{
		if (mMaterialSlots[i])
		{
			mMaterialSlots[i]->SetMaterial();
		}

		mTexture.lock()->SetShader(0, EShaderBufferType::Pixel, mAnimations[mState]->GetTextureInfoName());

		mMesh.lock()->Render();
	}
}

CAnimationComponent * CAnimationComponent::Clone()
{
	return new CAnimationComponent(*this);
}
