#include "TransformComponent.h"
#include "../Object/SceneObject.h"

#include "../Component/AnimationComponent.h"

#include "../Shader/ConstantBuffer/TransformCBuffer.h"
#include "../Scene/Scene.h"

CTransformComponent::CTransformComponent()
{	
	mTransformCBuffer = std::make_shared<TransformCBuffer>();
	mTransformCBuffer->Init();
}

CTransformComponent::~CTransformComponent()
{
}

void CTransformComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
	
	AddVelocity(mAcceleration * DeltaTime);
	AddWorldPos(mVelocity * DeltaTime);

	mPrevVelocity = mVelocity;
}

void CTransformComponent::PreRender(float DeltaTime)
{
	CSceneComponent::PreRender(DeltaTime);

	if (mParentObj.lock()->FindComponent("Animation").expired())
	{
	
	}
	else if (IsUsingTextureScale) 
	{
		mAnimationSize = std::dynamic_pointer_cast<CAnimationComponent>(mParentObj.lock()->FindComponent("Animation").lock())->GetAnimationSize();
		mPivot = std::dynamic_pointer_cast<CAnimationComponent>(mParentObj.lock()->FindComponent("Animation").lock())->GetPivot();
		mmatScale.Scaling(FVector3D(mAnimationSize.x, mAnimationSize.y, 1.f));
		mmatRot.Rotation(mWorldRot);
		mmatTranslate.Translation(FVector3D(mWorldPos.x + mPivot.x, mWorldPos.y + mPivot.y, mWorldPos.z));
	}
	else
	{
		mmatScale.Scaling(mWorldScale);
		mmatRot.Rotation(mWorldRot);
		mmatTranslate.Translation(mWorldPos);
	}
	
	mmatWorld = mmatScale * mmatRot * mmatTranslate;

	mPrevLocalPos = mLocalPos;
	mPrevWorldPos = mWorldPos;
}

void CTransformComponent::Render()
{
	mTransformCBuffer->SetWorldMatrix(mmatWorld);
	mTransformCBuffer->SetViewMatrix(mScene.lock()->GetCamera()->GetViewMatrix());
	mTransformCBuffer->SetProjMatrix(mScene.lock()->GetCamera()->GetProjMatrix());

	mTransformCBuffer->UpdateBuffer();
}

bool CTransformComponent::Init()
{
	if (mParentObj.lock()->mParentObj.expired())
	{
	}
	else
	{
		mParentTransform = std::dynamic_pointer_cast<CTransformComponent>(mParentObj.lock()->mParentObj.lock()->FindComponent("Transform").lock());
		SetWorldScale(mParentTransform.lock()->mWorldScale);
		SetWorldRotation(mParentTransform.lock()->mWorldRot);
		SetWorldPos(mParentTransform.lock()->mWorldPos);
	}

	return true;
}

void CTransformComponent::SwitchUsingTextureScale()
{
	IsUsingTextureScale = !IsUsingTextureScale;
}

// Get
const FVector3D& CTransformComponent::GetLocalScale() const
{
	return mLocalScale;
}
const FVector3D& CTransformComponent::GetLocalRotation() const
{
	return mLocalRot;
}
const FVector3D& CTransformComponent::GetLocalPosition() const
{
	return mLocalPos;
}

const FVector3D& CTransformComponent::GetWorldScale() const
{
	return mWorldScale;
}
const FVector3D& CTransformComponent::GetWorldRotation() const
{
	return mWorldRot;
}
FVector3D& CTransformComponent::GetWorldPosition()
{
	return mWorldPos;
}

const FVector3D & CTransformComponent::GetVelocity() const
{
	return mVelocity;
}

// Local
// Scale
void CTransformComponent::SetLocalScale(const FVector3D& scale)
{
	mLocalScale = scale;

	if(mParentObj.lock()->mParentObj.expired())
	{
		mWorldScale = mLocalScale;
	}
	else
	{
		mWorldScale = mLocalScale * mParentTransform.lock()->mWorldScale;
	}

	auto iter = mParentObj.lock()->mChildObjList.begin();
	auto iterEnd = mParentObj.lock()->mChildObjList.end();

	for (; iter != iterEnd; iter++)
	{
		std::shared_ptr<CTransformComponent> Child = std::dynamic_pointer_cast<CTransformComponent>((*iter)->FindComponent("Transform").lock());

		Child.get()->SetWorldScale(Child.get()->mLocalScale * mWorldScale);
	}
}

void CTransformComponent::SetLocalScale(const FVector2D & scale)
{
	SetLocalScale(FVector3D(scale.x, scale.y, mLocalScale.z));
}

void CTransformComponent::SetLocalScale(float x,float y,float z)
{
	SetLocalScale(FVector3D(x, y, z));
}

void CTransformComponent::SetLocalScale(float x,float y)
{
	SetLocalScale(FVector3D(x, y, mLocalScale.z));
}

// Rotation

void CTransformComponent::SetLocalRotation(const FVector3D & rot)
{
	mLocalRot = rot;

	if(mParentObj.lock()->mParentObj.expired())
	{
		mWorldRot = mLocalRot;
	}
	else
	{
		mWorldRot = mLocalRot + mParentTransform.lock().get()->mWorldRot;
	}

	auto iter = mParentObj.lock()->mChildObjList.begin();
	auto iterEnd = mParentObj.lock()->mChildObjList.end();

	FMatrix matRot;
	matRot.Rotation(mWorldRot);

	for (; iter != iterEnd; iter++)
	{
		std::shared_ptr<CTransformComponent> Child = std::dynamic_pointer_cast<CTransformComponent>((*iter)->FindComponent("Transform").lock());

		Child.get()->SetWorldPos((Child.get()->mLocalPos).TransformNormal(matRot) + mWorldPos);

		Child.get()->SetWorldRotation(Child.get()->mLocalRot + mWorldRot);
	}
}

void CTransformComponent::SetLocalRotation(const FVector2D & rot)
{
	SetLocalRotation(FVector3D(rot.x, rot.y, mLocalRot.z));
}

void CTransformComponent::SetLocalRotation(float x,float y,float z)
{
	SetLocalRotation(FVector3D(x, y, z));
}

void CTransformComponent::SetLocalRotation(float x,float y)
{
	SetLocalRotation(FVector3D(x, y, mLocalRot.z));
}

void CTransformComponent::SetLocalRotationX(float x)
{
	SetLocalRotation(FVector3D(x, mLocalRot.y, mLocalRot.z));
}

void CTransformComponent::SetLocalRotationY(float y)
{
	SetLocalRotation(FVector3D(mLocalRot.x, y, mLocalRot.z));
}

void CTransformComponent::SetLocalRotationZ(float z)
{
	SetLocalRotation(FVector3D(mLocalRot.x, mLocalRot.y, z));
}

// Position

void CTransformComponent::SetLocalPos(const FVector3D & pos)
{
	mLocalPos = pos;

	if(mParentObj.lock()->mParentObj.expired())
	{
		mWorldPos = mLocalPos;
	}
	else
	{
		FMatrix matRot;
		matRot.Rotation(mParentTransform.lock()->mWorldRot);

		mWorldPos = mLocalPos.TransformNormal(matRot) + mParentTransform.lock()->mWorldPos;
	}

	auto iter = mParentObj.lock()->mChildObjList.begin();
	auto iterEnd = mParentObj.lock()->mChildObjList.end();

	FMatrix matRot;
	matRot.Rotation(mWorldRot);

	for (; iter != iterEnd; iter++)
	{
		std::shared_ptr<CTransformComponent> Child = std::dynamic_pointer_cast<CTransformComponent>((*iter)->FindComponent("Transform").lock());

		Child.get()->SetWorldPos((Child.get()->mLocalPos).TransformNormal(matRot) + mWorldPos);
	}
}

void CTransformComponent::SetLocalPos(const FVector2D & pos)
{
	SetLocalPos(FVector3D(pos.x, pos.y, mLocalPos.z));
}

void CTransformComponent::SetLocalPos(float x,float y,float z)
{
	SetLocalPos(FVector3D(x, y, z));
}

void CTransformComponent::SetLocalPos(float x,float y)
{
	SetLocalPos(FVector3D(x, y, mLocalPos.z));
}

// World
// Scale

void CTransformComponent::SetWorldScale(const FVector3D& scale)
{
	mWorldScale = scale;

	if(mParentObj.lock()->mParentObj.expired())
	{
		mLocalScale = mWorldScale;;
	}
	else
	{
		mLocalScale = mWorldScale / mParentTransform.lock()->mWorldScale;
	}

	auto iter = mParentObj.lock().get()->mChildObjList.begin();
	auto iterEnd = mParentObj.lock().get()->mChildObjList.end();

	for (; iter != iterEnd; iter++)
	{
		std::shared_ptr<CTransformComponent> Child = std::dynamic_pointer_cast<CTransformComponent>((*iter)->FindComponent("Transform").lock());

		Child.get()->SetWorldScale(Child.get()->mLocalScale * mWorldScale);
	}
}

void CTransformComponent::SetWorldScale(const FVector2D & scale)
{
	SetWorldScale(FVector3D(scale.x, scale.y, mWorldScale.z));
}

void CTransformComponent::SetWorldScale(float x,float y,float z)
{
	SetWorldScale(FVector3D(x, y, z));
}

void CTransformComponent::SetWorldScale(float x,float y)
{
	SetWorldScale(FVector3D(x, y, mWorldScale.z));
}

// Rotation

void CTransformComponent::SetWorldRotation(const FVector3D & rot)
{
	mWorldRot = rot;

	if (mParentObj.lock()->mParentObj.expired())
	{
		mLocalRot = mWorldRot;
	}
	else
	{
		mLocalRot = mWorldRot - mParentTransform.lock()->mWorldRot;
	}

	auto iter = mParentObj.lock().get()->mChildObjList.begin();
	auto iterEnd = mParentObj.lock().get()->mChildObjList.end();

	FMatrix matRot;
	matRot.Rotation(mWorldRot);

	for (; iter != iterEnd; iter++)
	{
		std::shared_ptr<CTransformComponent> Child = std::dynamic_pointer_cast<CTransformComponent>((*iter)->FindComponent("Transform").lock());

		Child.get()->SetWorldPos((Child.get()->mLocalPos).TransformNormal(matRot) + mWorldPos);

		Child.get()->SetWorldRotation(Child.get()->mLocalRot + mWorldRot);
	}
}

void CTransformComponent::SetWorldRotation(const FVector2D & rot)
{
	SetWorldRotation(FVector3D(rot.x, rot.y, mWorldRot.z));
}

void CTransformComponent::SetWorldRotation(float x,float y,float z)
{
	SetWorldRotation(FVector3D(x, y, z));
}

void CTransformComponent::SetWorldRotation(float x,float y)
{
	SetWorldRotation(FVector3D(x, y, mWorldRot.z));
}

void CTransformComponent::SetWorldRotationX(float x)
{
	SetWorldRotation(FVector3D(x, mWorldRot.y, mWorldRot.z));
}

void CTransformComponent::SetWorldRotationY(float y)
{
	SetWorldRotation(FVector3D(mWorldRot.x, y, mWorldRot.z));
}

void CTransformComponent::SetWorldRotationZ(float z)
{
	SetWorldRotation(FVector3D(mWorldRot.x, mWorldRot.y, z));
}

// Position

void CTransformComponent::SetWorldPos(const FVector3D & pos)
{
	mWorldPos = pos;

	if (mParentObj.lock()->mParentObj.expired())
	{
		mLocalPos = mWorldPos;
	}
	else
	{
		FMatrix matRot;
		matRot.Rotation(mParentTransform.lock()->mWorldRot);
		matRot.Inverse();

		mLocalPos = (mWorldPos - mParentTransform.lock()->mWorldPos).TransformNormal(matRot);
	}

	auto iter = mParentObj.lock().get()->mChildObjList.begin();
	auto iterEnd = mParentObj.lock().get()->mChildObjList.end();

	FMatrix matRot;
	matRot.Rotation(mWorldRot);

	for (; iter != iterEnd; iter++)
	{
		std::shared_ptr<CTransformComponent> Child = std::dynamic_pointer_cast<CTransformComponent>((*iter)->FindComponent("Transform").lock());

		Child.get()->SetWorldPos((Child.get()->mLocalPos).TransformNormal(matRot) + mWorldPos);
	}
}

void CTransformComponent::SetWorldPos(const FVector2D & pos)
{
	SetWorldPos(FVector3D(pos.x, pos.y, mWorldPos.z));
}

void CTransformComponent::SetWorldPos(float x,float y,float z)
{
	SetWorldPos(FVector3D(x, y, z));
}

void CTransformComponent::SetWorldPos(float x,float y)
{
	SetWorldPos(FVector3D(x, y, mWorldPos.z));
}

void CTransformComponent::SetVelocity(const FVector3D & velocity)
{
	mVelocity = velocity;
}

void CTransformComponent::SetVelocity(const FVector2D & velocity)
{
	mVelocity = FVector3D(velocity.x, velocity.y, 0.f);
}

void CTransformComponent::SetVelocity(float x,float y,float z)
{
	mVelocity = FVector3D(x,y,z);
}

void CTransformComponent::SetVelocity(float x,float y)
{
	mVelocity = FVector3D(x,y,0.f);
}

void CTransformComponent::SetVelocityX(float x)
{
	mVelocity = FVector3D(x, mVelocity.y, mVelocity.z);
}

void CTransformComponent::SetVelocityY(float y)
{
	mVelocity = FVector3D(mVelocity.x, y, mVelocity.z);
}

void CTransformComponent::SetAcceleration(const FVector3D & Acceleration)
{
	mAcceleration = Acceleration;
}

void CTransformComponent::SetAcceleration(const FVector2D & Acceleration)
{
	mAcceleration = FVector3D(Acceleration.x, Acceleration.y, 0.f);
}

void CTransformComponent::SetAcceleration(float x,float y,float z)
{
	mAcceleration = FVector3D(x, y, z);
}

void CTransformComponent::SetAcceleration(float x,float y)
{
	mAcceleration = FVector3D(x, y, 0.f);
}

void CTransformComponent::SetAccelerationX(float x)
{
	mAcceleration = FVector3D(x, mAcceleration.y, mAcceleration.z);
}

void CTransformComponent::SetAccelerationY(float y)
{
	mAcceleration = FVector3D(mAcceleration.x, y, mAcceleration.z);
}

// Local
// Scale
void CTransformComponent::AddLocalScale(const FVector3D& scale)
{
	SetLocalPos(mLocalScale + scale);
}

void CTransformComponent::AddLocalScale(const FVector2D& scale)
{
	AddLocalScale(FVector3D(scale.x, scale.y, 0.f));
}

void CTransformComponent::AddLocalScale(float x,float y,float z)
{
	AddLocalScale(FVector3D(x, y, z));
}

void CTransformComponent::AddLocalScale(float x,float y)
{
	AddLocalScale(FVector3D(x, y, 0.f));
}

// Rotation
void CTransformComponent::AddLocalRotation(const FVector3D & rot)
{
	SetLocalRotation(mLocalRot + rot);
}

void CTransformComponent::AddLocalRotation(const FVector2D & rot)
{
	AddLocalRotation(FVector3D(rot.x, rot.y, 0.f));
}

void CTransformComponent::AddLocalRotation(float x,float y,float z)
{
	AddLocalRotation(FVector3D(x, y, z));
}

void CTransformComponent::AddLocalRotation(float x,float y)
{
	AddLocalRotation(FVector3D(x, y, 0.f));
}

void CTransformComponent::AddLocalRotationX(float x)
{
	AddLocalRotation(FVector3D(x, 0.f, 0.f));
}

void CTransformComponent::AddLocalRotationY(float y)
{
	AddLocalRotation(FVector3D(0.f, y, 0.f));
}

void CTransformComponent::AddLocalRotationZ(float z)
{
	AddLocalRotation(FVector3D(0.f, 0.f, z));
}

// Pos
void CTransformComponent::AddLocalPos(const FVector3D & pos)
{
	SetLocalPos(mLocalPos + pos);
}

void CTransformComponent::AddLocalPos(const FVector2D & pos)
{
	AddLocalPos(FVector3D(pos.x, pos.y, 0.f));
}

void CTransformComponent::AddLocalPos(float x,float y,float z)
{
	AddLocalPos(FVector3D(x, y, z));
}

void CTransformComponent::AddLocalPos(float x,float y)
{
	AddLocalPos(FVector3D(x, y, 0.f));
}

// World
// Scale
void CTransformComponent::AddWorldScale(const FVector3D & scale)
{
	SetWorldScale(mWorldScale + scale);
}

void CTransformComponent::AddWorldScale(const FVector2D & scale)
{
	AddWorldScale(FVector3D(scale.x, scale.y, 0.f));
}

void CTransformComponent::AddWorldScale(float x,float y,float z)
{
	AddWorldScale(FVector3D(x, y, z));
}

void CTransformComponent::AddWorldScale(float x,float y)
{
	AddWorldScale(FVector3D(x, y, 0.f));
}


void CTransformComponent::AddWorldRotation(const FVector3D & rot)
{
	SetWorldRotation(mWorldRot + rot);
}

void CTransformComponent::AddWorldRotation(const FVector2D & rot)
{
	AddWorldRotation(FVector3D(rot.x, rot.y, 0.f));
}

void CTransformComponent::AddWorldRotation(float x,float y,float z)
{
	AddWorldRotation(FVector3D(x, y, z));
}

void CTransformComponent::AddWorldRotation(float x,float y)
{
	AddWorldRotation(FVector3D(x, y, 0.f));
}

void CTransformComponent::AddWorldRotationX(float x)
{
	AddWorldRotation(FVector3D(x, 0.f, 0.f));
}

void CTransformComponent::AddWorldRotationY(float y)
{
	AddWorldRotation(FVector3D(0.f, y, 0.f));
}

void CTransformComponent::AddWorldRotationZ(float z)
{
	AddWorldRotation(FVector3D(0.f, 0.f, z));
}

// Pos
void CTransformComponent::AddWorldPos(const FVector3D & pos)
{
	SetWorldPos(mWorldPos + pos);
}

void CTransformComponent::AddWorldPos(const FVector2D & pos)
{
	AddWorldPos(FVector3D(pos.x, pos.y, 0.f));
}

void CTransformComponent::AddWorldPos(float x,float y,float z)
{
	AddWorldPos(FVector3D(x, y, z));
}

void CTransformComponent::AddWorldPos(float x,float y)
{
	AddWorldPos(FVector3D(x, y, 0.f));
}

// 회전축을 이용한 이동
void CTransformComponent::MoveDir(const FVector3D & v)
{
	FMatrix mat;
	mat.Rotation(mLocalRot);

	SetLocalPos(mLocalPos + v.TransformNormal(mat));
}

void CTransformComponent::AddVelocity(const FVector3D & velocity)
{
	mVelocity += velocity;
}

void CTransformComponent::AddVelocity(const FVector2D & velocity)
{
	mVelocity += FVector3D(velocity.x, velocity.y, 0.f);
}

void CTransformComponent::AddVelocity(float x,float y,float z)
{
	mVelocity += FVector3D(x, y, z);
}

void CTransformComponent::AddVelocity(float x,float y)
{
	mVelocity += FVector3D(x, y, 0.f);
}

void CTransformComponent::AddVelocityX(float x)
{
	mVelocity += FVector3D(x, 0.f, 0.f);
}

void CTransformComponent::AddVelocityY(float y)
{
	mVelocity += FVector3D(0.f, y, 0.f);
}

void CTransformComponent::AddAcceleration(const FVector3D & Acceleration)
{
	mAcceleration += Acceleration;
}

void CTransformComponent::AddAcceleration(const FVector2D & Acceleration)
{
	mAcceleration += FVector3D(Acceleration.x, Acceleration.y, 0.f);
}

void CTransformComponent::AddAcceleration(float x,float y,float z)
{
	mAcceleration += FVector3D(x,y,z);
}

void CTransformComponent::AddAcceleration(float x,float y)
{
	mAcceleration += FVector3D(x,y,0.f);
}

void CTransformComponent::AddAccelerationX(float x)
{
	mAcceleration += FVector3D(x, 0.f , 0.f);
}

void CTransformComponent::AddAccelerationY(float y)
{
	mAcceleration += FVector3D(0.f,y,0.f);
}

FVector3D CTransformComponent::GetPrevLocalPos()
{
	return mPrevLocalPos;
}

FVector3D CTransformComponent::GetPrevWorldPos()
{
	return mPrevWorldPos;
}

FVector3D CTransformComponent::GetPrevVelocity()
{
	return mPrevVelocity;
}
