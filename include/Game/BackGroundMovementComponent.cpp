#include "BackGroundMovementComponent.h"

#include "../Component/UITransformComponent.h"

#include "../Scene/Scene.h"
#include "../Object/SceneObject.h"

BackGroundMovementComponent::BackGroundMovementComponent()
{
}

BackGroundMovementComponent::~BackGroundMovementComponent()
{
	SAFE_DELETE(KirbyPosition);
}

bool BackGroundMovementComponent::Init()
{
	mTransformComponent = std::dynamic_pointer_cast<UITransformComponent>(mParentObj.lock()->FindComponent("Transform").lock());
	KirbyPosition = &std::dynamic_pointer_cast<CTransformComponent>(mScene.lock()->FindObject("Kirby").lock()->FindComponent("Transform").lock())->GetWorldPosition();

	if (mTransformComponent.expired() || KirbyPosition == nullptr)
		return false;

	return true;
}

void BackGroundMovementComponent::Update(float DeltaTime)
{
	mTransformComponent.lock()->SetWorldPos((*KirbyPosition) * -mSpeed);
	mTransformComponent.lock()->AddWorldPos(0.f, (*KirbyPosition).y * mSpeed * 0.5f, 0.f);
	mTransformComponent.lock()->UpdateMatrix();
}