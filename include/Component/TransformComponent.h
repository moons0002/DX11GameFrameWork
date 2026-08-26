#pragma once

#include "SceneComponent.h"

class CTransformComponent : public CSceneComponent
{
	friend class CSceneObject;
public:
	CTransformComponent();
	virtual ~CTransformComponent();

protected:
	std::weak_ptr<CTransformComponent> mParentTransform;

	std::shared_ptr<class TransformCBuffer> mTransformCBuffer;

	FVector2D mAnimationSize;
	FVector2D mPivot;

public:
	bool Init() override;

	void PostUpdate(float DeltaTime) override;

	void PreRender(float DeltaTime) override;
	void Render() override;

protected:
	FVector3D mLocalScale = FVector3D(1.f, 1.f, 1.f);
	FVector3D mLocalRot;
	FVector3D mLocalPos;

	FVector3D mWorldScale = FVector3D(1.f, 1.f, 1.f);
	FVector3D mWorldRot;
	FVector3D mWorldPos;

	FMatrix mmatScale;
	FMatrix mmatRot;
	FMatrix mmatTranslate;
	FMatrix mmatWorld;

	// 속도
	FVector3D mVelocity;
	// 가속도
	FVector3D mAcceleration;

	// 이전 위치
	FVector3D mPrevLocalPos;
	FVector3D mPrevWorldPos;
	FVector3D mPrevVelocity;
 
	// 텍스처 사이즈 이용
	bool IsUsingTextureScale = true;

public:
	void SwitchUsingTextureScale();

public:
	const FVector3D& GetLocalScale() const;
	const FVector3D& GetLocalRotation() const;
	const FVector3D& GetLocalPosition() const;

	const FVector3D& GetWorldScale() const;
	const FVector3D& GetWorldRotation() const;
	FVector3D& GetWorldPosition();

	const FVector3D& GetVelocity() const;

	// Local
	// Scale
	void SetLocalScale(const FVector3D& scale);
	void SetLocalScale(const FVector2D& scale);
	void SetLocalScale(float x, float y, float z);
	void SetLocalScale(float x, float y);

	// Rotation
	void SetLocalRotation(const FVector3D& rot);
	void SetLocalRotation(const FVector2D& rot);
	void SetLocalRotation(float x, float y, float z);
	void SetLocalRotation(float x, float y);

	void SetLocalRotationX(float x);
	void SetLocalRotationY(float y);
	void SetLocalRotationZ(float z);

	// Position
	void SetLocalPos(const FVector3D& pos);
	void SetLocalPos(const FVector2D& pos);
	void SetLocalPos(float x, float y, float z);
	void SetLocalPos(float x, float y);

	// World
	// Scale
	void SetWorldScale(const FVector3D& scale);
	void SetWorldScale(const FVector2D& scale);
	void SetWorldScale(float x, float y, float z);
	void SetWorldScale(float x, float y);

	// Rotation
	void SetWorldRotation(const FVector3D& rot);
	void SetWorldRotation(const FVector2D& rot);
	void SetWorldRotation(float x, float y, float z);
	void SetWorldRotation(float x, float y);

	void SetWorldRotationX(float x);
	void SetWorldRotationY(float y);
	void SetWorldRotationZ(float z);

	// Position
	void SetWorldPos(const FVector3D& pos);
	void SetWorldPos(const FVector2D& pos);
	void SetWorldPos(float x, float y, float z);
	void SetWorldPos(float x, float y);

	// Velocity
	void SetVelocity(const FVector3D& velocity);
	void SetVelocity(const FVector2D& velocity);
	void SetVelocity(float x, float y, float z);
	void SetVelocity(float x, float y);

	void SetVelocityX(float x);
	void SetVelocityY(float y);

	// Acceleration
	void SetAcceleration(const FVector3D& Acceleration);
	void SetAcceleration(const FVector2D& Acceleration);
	void SetAcceleration(float x, float y, float z);
	void SetAcceleration(float x, float y);

	void SetAccelerationX(float x);
	void SetAccelerationY(float y);

public:
	// Local
	// Scale
	void AddLocalScale(const FVector3D& scale);
	void AddLocalScale(const FVector2D& scale);
	void AddLocalScale(float x, float y, float z);
	void AddLocalScale(float x, float y);

	// Rotation
	void AddLocalRotation(const FVector3D& rot);
	void AddLocalRotation(const FVector2D& rot);
	void AddLocalRotation(float x, float y, float z);
	void AddLocalRotation(float x, float y);

	void AddLocalRotationX(float x);
	void AddLocalRotationY(float y);
	void AddLocalRotationZ(float z);

	// Position
	void AddLocalPos(const FVector3D& pos);
	void AddLocalPos(const FVector2D& pos);
	void AddLocalPos(float x, float y, float z);
	void AddLocalPos(float x, float y);

	// World
	// Scale
	void AddWorldScale(const FVector3D& scale);
	void AddWorldScale(const FVector2D& scale);
	void AddWorldScale(float x, float y, float z);
	void AddWorldScale(float x, float y);

	// Rotation
	void AddWorldRotation(const FVector3D& rot);
	void AddWorldRotation(const FVector2D& rot);
	void AddWorldRotation(float x, float y, float z);
	void AddWorldRotation(float x, float y);

	void AddWorldRotationX(float x);
	void AddWorldRotationY(float y);
	void AddWorldRotationZ(float z);

	// Position
	void AddWorldPos(const FVector3D& pos);
	void AddWorldPos(const FVector2D& pos);
	void AddWorldPos(float x, float y, float z);
	void AddWorldPos(float x, float y);

	void MoveDir(const FVector3D& v);

	// Velocity
	void AddVelocity(const FVector3D& velocity);
	void AddVelocity(const FVector2D& velocity);
	void AddVelocity(float x, float y, float z);
	void AddVelocity(float x, float y);

	void AddVelocityX(float x);
	void AddVelocityY(float y);

	// Acceleration
	void AddAcceleration(const FVector3D& Acceleration);
	void AddAcceleration(const FVector2D& Acceleration);
	void AddAcceleration(float x, float y, float z);
	void AddAcceleration(float x, float y);

	void AddAccelerationX(float x);
	void AddAccelerationY(float y);

	// Prev

	FVector3D GetPrevLocalPos();
	FVector3D GetPrevWorldPos();
	FVector3D GetPrevVelocity();
};

