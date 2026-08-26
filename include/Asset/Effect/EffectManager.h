#pragma once
#pragma once

#include "../../Shader/ConstantBuffer/AnimationCBuffer.h"
#include "../Animation/Animaiton.h"

#include "../../Component/AnimationComponent.h"
#include "../../Component/TransformComponent.h"

#include "../../Object/SceneObject.h"
#include "../../Scene/Scene.h"

class TransformCBuffer;

class CMaterial;
class CTexture;

struct FEffectData
{
	// 어떤 이름의 이펙트를 쓸것인가
	std::string mAnimationInfoName;
	// 특정 Transform을 참조 할거냐도 정해야 할듯?
	std::weak_ptr<CTransformComponent> mTransform;

	// 시작 시간
	float mStartTime = 0.f;
	// 재생 시간
	float mPlayTime = 0.f;

	int Index = 0;

	// 위치
	FVector3D mPosition;

	FVector3D PrevRot;
	FVector3D PrevPos;
	FMatrix PrevView;
	FMatrix PrevProj;

	FEffectData(std::string AnimationInfoName, float PlayTime, FVector3D Position, std::weak_ptr<CTransformComponent> Transform)
	{
		mAnimationInfoName = AnimationInfoName;
		mPlayTime = PlayTime;
		mPosition = Position;
		mTransform = Transform;

		PrevRot = mTransform.lock()->GetWorldRotation();
		PrevPos = mTransform.lock()->GetWorldPosition();
		PrevView = mTransform.lock()->GetParentObj().lock()->GetScene().lock()->GetCamera()->GetViewMatrix();
		PrevProj = mTransform.lock()->GetParentObj().lock()->GetScene().lock()->GetCamera()->GetProjMatrix();
	};
	~FEffectData()
	{
		//SAFE_DELETE(mPosition);
	}
};

class CEffectManager
{
public:
	CEffectManager();
	virtual ~CEffectManager();

protected:
	// 현재 실행중인 Effects
	std::vector<FEffectData> mEffects;

	std::weak_ptr<class CShader> mShader;
	std::weak_ptr<class CMesh> mMesh;

	std::vector<std::shared_ptr<CMaterial>> mMaterialSlots;
	// map의 key를 이용해서 사용, pair->first는 Texture, second는 그 Texture의 정보?
	std::map<std::string, std::pair<std::string, std::shared_ptr<CAnimation>>> mAnimations;

	std::shared_ptr<TransformCBuffer> mTransformCBuffer;
	std::shared_ptr<CAnimationCBuffer> mAnimationCBuffer;

protected:
	float Time = 0.f;
	float DeltaTime = 0.f;

	std::string mState;

public:
	void SetShader(const std::string& Name);
	void SetShader(std::shared_ptr<CShader> Shader);

	void SetMesh(const std::string& Name);
	void SetMesh(std::shared_ptr<CMesh> Mesh);

	// 중간에 머티리얼을 변경할수있게 함수를 제공한다.
	void SetMaterial(int SlotIndex, const std::string Name);
	void SetMaterial(int SlotIndex, std::shared_ptr<CMaterial> Material);

public:
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

	void AddAnimation(const std::string& TextureName, const std::string& AnimationInfoName, const std::string& AnimationName,
		FVector2D Start, FVector2D Size, FVector2D Padding, int Col, int Row);
	// 원하는 State로 변경하고, 특정 Frame를 보여주자
	void ChangeState(const std::string& State, int FrameIndex = 0);

public:
	void PlayEffect(std::string AnimationInfoName, float PlayTime, FVector3D Position, std::weak_ptr<CTransformComponent> mTransform);

public:
	bool Init();

	void PreUpdate(float DeltaTime);

	void Render();

	virtual CEffectManager* Clone();

	void UpdateTransform(std::vector<FEffectData>::iterator iter);
};