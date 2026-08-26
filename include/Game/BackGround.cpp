#include "BackGround.h"

#include "../Component/AnimationComponent.h"
#include "../Component/UITransformComponent.h"

#include "BackGroundMovementComponent.h"

#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"

bool BackGround::Init()
{
	// Transform
	CreateComponent<UITransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<UITransformComponent>(FindComponent("Transform").lock());
	Transform->SetLocalScale(1.3f, 1.f, 1.f);

	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());

	Animation->SetTexture("BackGround");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(-100);
	
	// 1. 애니메이션을 추가한다
	Animation->AddAnimation("BackGround_0", "BackGround_0", FVector2D(0.f, 0.f), FVector2D(672.f, 216.f), FVector2D(0.f, 0.f), 1, 1);
	Animation->ChangeState("BackGround_0", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(1);

	//
	CreateComponent<BackGroundMovementComponent>("BackGroundMovement");

	Transform->UpdateMatrix();

	return true;
}
