#include "MaterialManager.h"
#include "Material.h"

#include "../AssetManager.h"

CMaterialManager::CMaterialManager()
{
}

CMaterialManager::~CMaterialManager()
{
	CMaterial::DestroySampler();
}

bool CMaterialManager::Init()
{
	CMaterial::SetSampler(ETextureSamplerType::Point);
	CMaterial::SetSampler(ETextureSamplerType::Linear);
	CMaterial::SetSampler(ETextureSamplerType::Anisotropic);

	return true;
}

bool CMaterialManager::CreateMaterial(const std::string& Name)
{
	if (FindMaterial(Name))
	{
		return false;
	}

	std::shared_ptr<CMaterial> Material = std::make_shared<CMaterial>();

	Material->SetName(Name);

	mMaterialMap.insert(std::make_pair(Name, Material));

	return true;
}

std::shared_ptr<CMaterial> CMaterialManager::FindMaterial(const std::string& Name)
{
	auto iter = mMaterialMap.find(Name);

	if (iter == mMaterialMap.end())
	{
		return nullptr;
	}
	return iter->second;
}

void CMaterialManager::ReleaseMaterial(class CAsset* Material)
{
	auto iter = mMaterialMap.find(Material->GetName());

	if (iter != mMaterialMap.end())
	{
		mMaterialMap.erase(iter);
	}
}

void CMaterialManager::InitAllMaterial()
{
	CreateMaterial("DefaultMaterial");

	std::shared_ptr<CMaterial> Mtrl = FindMaterial("DefaultMaterial");

	Mtrl->SetPixelShader("DefaultAnimationShader");
	Mtrl->SetSamplerType(ETextureSamplerType::Point);
}
