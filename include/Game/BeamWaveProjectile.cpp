#include "BeamWaveProjectile.h"

#include "../Component/AnimationComponent.h"
#include "../Component/TransformComponent.h"

#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"

#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"

#include "BeamWaveCenter.h"

bool BeamWaveProjectile::Init()
{
	CreateComponent<CTransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());
	Transform->SetLocalScale(1.5f, 1.5f, 1.f);
	Transform->SwitchUsingTextureScale();

	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	// Kirby라는 이름의 텍스처를 사용할것이다
	Animation->SetTexture("BeamObject");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(5);
	
	// 1. 애니메이션을 추가한다
	Animation->AddAnimation("BeamObject", "BeamWaveProjectile", FVector2D(82.f, 0.f), FVector2D(33.f, 29.f), FVector2D(0.f, 0.f), 1, 1);
	Animation->ChangeState("BeamWaveProjectile", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(1);

	// Collider
	//CreateComponent<CColliderOBB2D>("Collider");
	//auto Collider = std::dynamic_pointer_cast<CColliderOBB2D>(FindComponent("Collider").lock());
	//mScene.lock()->AddCollider(Collider);

	return true;
}
