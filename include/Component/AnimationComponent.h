#pragma once

#include "SceneComponent.h"
#include "../Shader/ConstantBuffer/AnimationCBuffer.h"
#include "../Asset/Animation/Animaiton.h"

class CMaterial;
class CTexture;

class CAnimationComponent : public CSceneComponent
{
public:
	CAnimationComponent();
	virtual ~CAnimationComponent();

protected:
	std::weak_ptr<class CShader> mShader;
	std::weak_ptr<class CMesh> mMesh;

	// Animation의 이름과 SetMaterial할때 이름 맞춰주기
	std::vector<std::shared_ptr<CMaterial>> mMaterialSlots;
	std::map<std::string, std::shared_ptr<CAnimation>> mAnimations;

	// 이 컴포넌트가 어떤 텍스처를 쓸것인가
	std::weak_ptr<CTexture> mTexture;

	// mState에 맞게 특정 Animation의 정보를 얻어온다
	std::string mState;

	int mSortingOrder = 0;

	std::shared_ptr<CAnimationCBuffer> mAnimationCBuffer;

public:
	void SetShader(const std::string& Name);
	void SetShader(std::shared_ptr<CShader> Shader);

	void SetMesh(const std::string& Name);
	void SetMesh(std::shared_ptr<CMesh> Mesh);

	void SetSortingOrder(int Order);
	int GetSortingOrder();

public:
	// 중간에 머티리얼을 변경할수있게 함수를 제공한다.
	void SetMaterial(int SlotIndex, const std::string Name);
	void SetMaterial(int SlotIndex, std::shared_ptr<CMaterial> Material);

private:
	// 텍스쳐 가져오기
	// File Name
	void AddTexture(int SlotIndex, const std::string& Name,
		const TCHAR* FileName,
		int Register,
		int ShaderBufferType,
		const std::string& TextureName);
public:
	//BaseColor
	void SetBaseColor(int SlotIndex, float r, float g, float b, float a);
	//Opacity
	void SetOpacity(int SlotIndex, float Opacity);
	void AddOpacity(int SlotIndex, float Opacity);
	float GetOpacity(int SlotIndex);

public:
	void SetTexture(const std::string& TextureName);

	void AddAnimation(const std::string& AnimationName, std::shared_ptr<CAnimation> Animation);
	void AddAnimation(const std::string& AnimationInfoName, const std::string& AnimationName, FVector2D Start, FVector2D Size, FVector2D Padding, int Col, int Row);

	// 원하는 State로 변경하고, 특정 Frame를 보여주자
	void ChangeState(const std::string& State, int FrameIndex = 0);
	// 특정 Frame으로 변경
	void ChangeFrame(int FrameIndex);
	// 다음 Frame으로 변경
	void ChangeNextFrame(float DeltaTime);
	// 현재 상태에서 뒤집기
	void FlipHorizon();
	void FlipVertical();

	void SetSpeed(float Speed);
	void SetPlayOption(FAnimationPlayOption PlayOption);
	void SetFlip(bool Horizon, bool Vertical);
	void SetRepeatIndex(int Index);

	void SetPivot(float x, float y);

	FVector2D& GetAnimationSize();
	FVector2D& GetPivot();

public:
	virtual bool Init();
	virtual bool Init(const char* FileName);

	virtual void PreRender(float DeltaTime) override;
	virtual void Render() override;

	virtual CAnimationComponent* Clone();

};