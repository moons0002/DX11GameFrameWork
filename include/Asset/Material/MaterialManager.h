#pragma once

#include "../../Gameinfo.h"

class CMaterial;

class CMaterialManager
{
public:
	CMaterialManager();
	~CMaterialManager();

private:
	std::unordered_map<std::string, std::shared_ptr<CMaterial>> mMaterialMap;

public:
	bool Init();

	bool CreateMaterial(const std::string& Name);
	std::shared_ptr<CMaterial> FindMaterial(const std::string& Name);
	void ReleaseMaterial(class CAsset* Texture);

	// 설정이 다 끝나고 Material 추가
	void InitAllMaterial();
};

