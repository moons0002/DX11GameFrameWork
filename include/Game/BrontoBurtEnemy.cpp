#include "BrontoBurtEnemy.h"

#include "../Component/SceneComponent.h"
#include "../Component/AnimationComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"

#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"
#include "../Object/SceneObject.h"

#include "../Component/MovementConstraintComponent.h"

bool BrontoBurtEnemy::Init()
{
	CEnemyObject::Init();

	// Transform
	CreateComponent<CTransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());
	Transform->SetLocalScale(24.f, 24.f, 1.f);

	// Collider
	CreateComponent<CColliderAABB2D>("Collider");
	auto Collider = std::dynamic_pointer_cast<CColliderAABB2D>(FindComponent("Collider").lock());
	Collider->UpdateTransform();
	mScene.lock()->AddCollider(Collider);
	
	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	
	Animation->SetTexture("BrontoBurt");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(5);
	
	// 1. 애니메이션을 추가한다
	Animation->AddAnimation("BrontoBurt", "Idle", FVector2D(0, 0), FVector2D(40.f, 32.f), FVector2D(0.f, 0.f), 3, 1);
	Animation->ChangeState("Idle", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::PingPong);
	Animation->SetSpeed(30);
	Animation->SetPivot(5, 0);

	// 2
	Animation->AddAnimation("BrontoBurt", "Damaged", FVector2D(40.f * 13, 0), FVector2D(40.f, 32.f), FVector2D(0.f, 0.f), 1, 1);
	Animation->ChangeState("Damaged", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::PingPong);
	Animation->SetSpeed(30);

	//
	Animation->ChangeState("Idle");

	CreateComponent<MovementConstraintComponent>("MovementConstraint");

	mDamage = 30.f;

	return true;
}

void BrontoBurtEnemy::PreRender(float DeltaTime)
{
	InhalableEnemyObject::PreRender(DeltaTime);
	if (IsInhaled)
	{
		std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock())->ChangeState("Damaged");
	}
	else
	{
		std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock())->ChangeState("Idle");
	}
}

void BrontoBurtEnemy::EnemyMoving()
{
	auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());
	if (IsInhalingEnd == true)
	{
		return;
	}
	else
	{
	}
}
