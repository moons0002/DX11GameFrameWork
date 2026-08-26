#pragma once

#include "SceneComponent.h"

class CMaterial;
class CTexture;

class CStaticMeshComponent : public CSceneComponent
{
	friend class CSceneObject;
public:
	CStaticMeshComponent();
	virtual ~CStaticMeshComponent();

protected:
	std::weak_ptr<class CShader> mShader;
	std::weak_ptr<class CMesh> mMesh;

	std::vector<std::shared_ptr<CMaterial>> mMaterialSlots;

	int mSortingOrder = 0;

public:
	void SetShader(const std::string& Name);
	void SetShader(std::shared_ptr<CShader> Shader);
	void SetMesh(const std::string& Name);
	void SetMesh(std::shared_ptr<CMesh> Mesh);
	void SetSortingOrder(int Order);
	int GetSortingOrder();

	// 중간에 머티리얼을 변경할수있게 함수를 제공한다.
	void SetMaterial(int SlotIndex, const std::string Name);
	void SetMaterial(int SlotIndex, std::shared_ptr<CMaterial> Material);

	// 텍스쳐 가져오기
	//파일 이름으로 텍스쳐 매니져에서 로드 후 추가하기 
	void AddTexture(int SlotIndex, const std::string& Name,
		const TCHAR* FileName,
		int Register,
		int ShaderBufferType,
		const std::string& TextureName);

	//BaseColor
	void SetBaseColor(int SlotIndex, float r, float g, float b, float a);
	//Opacity
	void SetOpacity(int SlotIndex, float Opacity);

public:
	virtual bool Init();
	virtual bool Init(const char* FileName);

	virtual void Render() override;

	virtual CStaticMeshComponent* Clone();
};