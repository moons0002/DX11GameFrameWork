#include "StaticMeshComponent.h"

#include "../Shader/ShaderManager.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Material/Material.h"

#include "../Render/RenderManager.h"

CStaticMeshComponent::CStaticMeshComponent()
{
}

CStaticMeshComponent::~CStaticMeshComponent()
{
}

void CStaticMeshComponent::SetShader(const std::string & Name)
{
	mShader = CShaderManager::GetInstance().FindShader(Name);
}

void CStaticMeshComponent::SetShader(std::shared_ptr<CShader> Shader)
{
	mShader = Shader;
}

void CStaticMeshComponent::SetMesh(const std::string & Name)
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

void CStaticMeshComponent::SetMesh(std::shared_ptr<CMesh> Mesh)
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

void CStaticMeshComponent::SetSortingOrder(int Order)
{
	mSortingOrder = Order;
}

int CStaticMeshComponent::GetSortingOrder()
{
	return mSortingOrder;
}

//머티리얼 변경
void CStaticMeshComponent::SetMaterial(int SlotIndex, const std::string Name)
{
	std::shared_ptr<CMaterial> Material = nullptr;

	Material = CAssetManager::GetInstance().GetMaterialManager()->FindMaterial(Name);

	if (Material)
	{
		Material = Material->Clone();
	}

	mMaterialSlots[SlotIndex] = Material;
}

void CStaticMeshComponent::SetMaterial(int SlotIndex, std::shared_ptr<CMaterial> Material)
{
	mMaterialSlots[SlotIndex] = Material;
}

void CStaticMeshComponent::AddTexture(int SlotIndex, const std::string& Name, const TCHAR* FileName, int Register,
	int ShaderBufferType, const std::string& TextureName)
{
	CAssetManager::GetInstance().GetTextureManager()->LoadTexture(Name, FileName, TextureName);
}

void CStaticMeshComponent::SetBaseColor(int SlotIndex, float r, float g, float b, float a)
{
	mMaterialSlots[SlotIndex]->SetBaseColor(r, g, b, a);
}

void CStaticMeshComponent::SetOpacity(int SlotIndex, float Opacity)
{
	mMaterialSlots[SlotIndex]->SetOpacity(Opacity);
}

bool CStaticMeshComponent::Init()
{
	SetShader("StaticMeshShader");

	CRenderManager::GetInstance().PushBackRenderList(mParentObj);

	return true;
}

bool CStaticMeshComponent::Init(const char* FileName)
{
	SetShader("StaticMeshShader");

	CRenderManager::GetInstance().PushBackRenderList(mParentObj);

	return true;
}

void CStaticMeshComponent::Render()
{
	CSceneComponent::Render();

	mShader.lock()->SetShader();

	int SlotCount = mMesh.lock()->GetSlotCount();

	for (int i = 0; i < SlotCount; ++i)
	{
		if (mMaterialSlots[i])
		{
			mMaterialSlots[i]->SetMaterial();
		}

		mMesh.lock()->Render();
	}

	mMesh.lock()->Render();
}

CStaticMeshComponent * CStaticMeshComponent::Clone()
{
	return new CStaticMeshComponent(*this);
}
