#include "GravityComponent.h"

#include "../Object/SceneObject.h"

bool GravityComponent::Init()
{
	mTransform = std::dynamic_pointer_cast<CTransformComponent>(mParentObj.lock()->FindComponent("Transform").lock());
	mKirby = std::dynamic_pointer_cast<KirbyStateComponent>(mParentObj.lock()->FindComponent("KirbyState").lock());

	return true;
}

void GravityComponent::PreUpdate(float DeltaTime)
{
	if (!mKirby.expired())
	{
		if (mTransform.lock()->GetVelocity().y == 0.f && mTransform.lock()->GetPrevVelocity().y <= 0.f)
		{
			mKirby.lock()->OnGround();
		}
		else
		{
			mKirby.lock()->NotOnGround();
		}
	}
	mTransform.lock()->SetAccelerationY(-250.f);
}
