#include "BeamEnemy.h"

#include "../Component/SceneComponent.h"
#include "../Component/AnimationComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"

#include "../Asset/AssetManager.h"
#include "../Component/GravityComponent.h"
#include "../Component/MovementConstraintComponent.h"

#include "../Scene/Scene.h"
#include "../Object/SceneObject.h"

bool BeamEnemy::Init()
{
	CEnemyObject::Init();

	mInhalableEnemyType = EInhalableEnemyType::Beam;

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
	
	Animation->SetTexture("Beam");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(5);
	
	// 1. 애니메이션을 추가한다
	Animation->AddAnimation("Walk", "Walk", FVector2D(0, 0), FVector2D(40.f, 40.f), FVector2D(0.f, 0.f), 5, 1);
	Animation->ChangeState("Walk", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::PingPong);
	Animation->SetSpeed(30);

	// 2
	Animation->AddAnimation("Damaged", "Damaged", FVector2D(0, 0), FVector2D(32.f, 32.f), FVector2D(0.f, 0.f), 1, 1);
	Animation->ChangeState("Damaged", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::PingPong);
	Animation->SetSpeed(30);

	//
	Animation->ChangeState("Walk");

	CreateComponent<GravityComponent>("Gravity");
	CreateComponent<MovementConstraintComponent>("MovementConstraint");

	mDamage = 50.f;

	return true;
}

void BeamEnemy::PreRender(float DeltaTime)
{
	InhalableEnemyObject::PreRender(DeltaTime);
	if (IsInhaled || IsInhalingEnd)
	{
		std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock())->ChangeState("Damaged");
	}
	else
	{
		std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock())->ChangeState("Walk");
	}
}

void BeamEnemy::EnemyMoving()
{
	auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());
	if (IsInhalingEnd == true)
	{
		return;
	}
	else
	{
		Transform->SetVelocityX(20.f);
	}
}