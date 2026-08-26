#include "KirbyDamage.h"

#include "../Object/SceneObject.h"
#include "../Component/SceneComponent.h"

#include "../Component/TransformComponent.h"
#include "../Component/ColliderBase.h"

#include "EnemyObject.h"

bool KirbyDamage::Init()
{
	mTransform = std::dynamic_pointer_cast<CTransformComponent>(mParentObj.lock()->FindComponent("Transform").lock());
	mCollision = std::dynamic_pointer_cast<CColliderBase>(mParentObj.lock()->FindComponent("Collider").lock());
	mKirbyState = std::dynamic_pointer_cast<KirbyStateComponent>(mParentObj.lock()->FindComponent("KirbyState").lock());
	mKirby = std::dynamic_pointer_cast<KirbyObject>(mParentObj.lock());

	return true;
}

void KirbyDamage::Collision(float DeltaTime)
{
	if (mKirbyState->IsGod()) return;

	mObject = mCollision->GetCollisionObjList().back().lock()->GetParentObj().lock();
	if (mObject->GetObjectType() == ObjectType::Enemy)
	{
		if (mTransform->GetWorldPosition().x < std::dynamic_pointer_cast<CTransformComponent>(mObject->FindComponent("Transform").lock())->GetWorldPosition().x)
		{
			mTransform->SetVelocity(-50.f, 0.f);
		}
		else
		{
			mTransform->SetVelocity(50.f, 0.f);
		}

		mKirby->AddHp(-std::dynamic_pointer_cast<CEnemyObject>(mObject)->GetDamage());
		mKirby->SetState("Damage");
		mKirbyState->Damaged();
	}
}
