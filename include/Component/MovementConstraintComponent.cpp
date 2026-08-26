#include "MovementConstraintComponent.h"

#include "../Scene/Scene.h"

bool MovementConstraintComponent::Init()
{
	mTransform = std::dynamic_pointer_cast<CTransformComponent>(mParentObj.lock()->FindComponent("Transform").lock());
	if (mTransform.expired()) return false;

	mCollision = std::dynamic_pointer_cast<CColliderBase>(mParentObj.lock()->FindComponent("Collider").lock());
	if (mCollision.expired()) return false;

	return true;
}

void MovementConstraintComponent::Collision(float DeltaTime)
{
	if (mCollision.lock()->GetCollisionObjList().back().lock()->GetColliderSurface() == EColliderSurface::Ground ||
		mCollision.lock()->GetCollisionObjList().back().lock()->GetColliderSurface() == EColliderSurface::Wall ||
		mCollision.lock()->GetCollisionObjList().back().lock()->GetColliderSurface() == EColliderSurface::Ceiling)
	{
		mTransform.lock()->SetWorldPos(mTransform.lock()->GetPrevWorldPos());

		mTransform.lock()->AddWorldPos(mTransform.lock()->GetVelocity().x * DeltaTime, 0.f);
		mCollision.lock()->UpdateTransform();
		if (mCollision.lock()->CheckCollision(mCollision.lock()->GetCollisionObjList().back().lock(), DeltaTime))
		{
			if (mTransform.lock()->GetVelocity().x > 0)
			{
				mTransform.lock()->SetWorldPos(mCollision.lock()->GetCollisionObjList().back().lock()->GetMin().x - mTransform.lock()->GetWorldScale().x / 2.f, 
					mTransform.lock()->GetWorldPosition().y);
				mTransform.lock()->SetVelocityX(0.f);
			}
			else if (mTransform.lock()->GetVelocity().x < 0)
			{
				mTransform.lock()->SetWorldPos(mCollision.lock()->GetCollisionObjList().back().lock()->GetMax().x + mTransform.lock()->GetWorldScale().x / 2.f, 
					mTransform.lock()->GetWorldPosition().y);
				mTransform.lock()->SetVelocityX(0.f);
			}
		}

		mTransform.lock()->AddWorldPos(0.f, mTransform.lock()->GetVelocity().y * DeltaTime);
		mCollision.lock()->UpdateTransform();
		if (mCollision.lock()->CheckCollision(mCollision.lock()->GetCollisionObjList().back().lock(), DeltaTime))
		{
			if (mTransform.lock()->GetVelocity().y > 0)
			{
				mTransform.lock()->SetWorldPos(mTransform.lock()->GetWorldPosition().x,
					mCollision.lock()->GetCollisionObjList().back().lock()->GetMin().y - mTransform.lock()->GetWorldScale().y / 2.f);
				mTransform.lock()->SetVelocityY(0.f);
			}
			else if (mTransform.lock()->GetVelocity().y < 0)
			{
				mTransform.lock()->SetWorldPos(mTransform.lock()->GetWorldPosition().x,
					mCollision.lock()->GetCollisionObjList().back().lock()->GetMax().y + mTransform.lock()->GetWorldScale().y / 2.f);
				mTransform.lock()->SetVelocityY(0.f);
			}
		}
	}
}