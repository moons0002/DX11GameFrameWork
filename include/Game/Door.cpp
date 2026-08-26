#include "Door.h"

#include "../Component/AnimationComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderLine2D.h"
#include "../Component/MapColliderAABB2D.h"

#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"

bool Door::Init()
{
	mObjectType = ObjectType::Door;

	// Transform
	CreateComponent<CTransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());

	// Collider
	CreateComponent<MapColliderAABB2D>("Collider");
	auto Collider = std::dynamic_pointer_cast<MapColliderAABB2D>(FindComponent("Collider").lock());
	Collider->SetCenter(FVector3D(0.f, 0.f, 0.f));
	Collider->SetSize(FVector3D(5.f, 30.f, 0.f));
	Collider->SetColliderSurface(EColliderSurface::Pass);
	Collider->UpdateTransform();
	mScene.lock()->AddCollider(Collider);

	// 충돌 표시 위한 애니메이션
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	Animation->SetTexture("BeamObject");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(10);
	Animation->AddAnimation("BeamObject", "Default", FVector2D(0.f, 0.f), FVector2D(1.f, 1.f), FVector2D(0.f, 0.f), 1, 1);
	Animation->ChangeState("Default", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(1);

	return true;
}

void Door::SetToPosition(FVector2D Position)
{
	ToPosition = Position;
}

FVector2D Door::GetToPosition()
{
	return ToPosition;
}

void Door::SetToStage(std::string Stage)
{
	ToStage = Stage;
}

std::string & Door::GetToStage()
{
	return ToStage;
}
