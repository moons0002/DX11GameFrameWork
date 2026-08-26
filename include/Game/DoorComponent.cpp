#include "DoorComponent.h"

#include "KirbyObject.h"

#include "Door.h"
#include "../Scene/Scene.h"

#include "FadeInOut.h"

bool DoorComponent::Init()
{
	Transform = std::dynamic_pointer_cast<CTransformComponent>(mParentObj.lock()->FindComponent("Transform").lock());
	Collider = std::dynamic_pointer_cast<CColliderBase>(mParentObj.lock()->FindComponent("Collider").lock());
	return true;
}

void DoorComponent::Collision(float DeltaTime)
{
	CSceneComponent::Collision(DeltaTime);
	if (IsCheckingDoor)
	{
		if (Collider.lock()->GetCollisionObjList().back().lock()->GetParentObj().lock()->GetObjectType() == ObjectType::Door)
		{
			mDoor = std::dynamic_pointer_cast<Door>(Collider.lock()->GetCollisionObjList().back().lock()->GetParentObj().lock());
		}
	}
}

void DoorComponent::PreRender(float DeltaTime)
{
	CSceneComponent::PreRender(DeltaTime);
	if (mDoor)
	{
		mScene.lock()->StartChangeStage(mDoor->GetToStage(), mDoor->GetToPosition());
		mDoor = nullptr;
	}
	IsCheckingDoor = false;
}

void DoorComponent::CheckDoor()
{
	IsCheckingDoor = true;
}