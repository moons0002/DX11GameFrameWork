#include "StageIcon.h"

#include "../Component/AnimationComponent.h"
#include "../Component/UITransformComponent.h"

#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"

bool StageIcon::Init()
{
	// Transform
	CreateComponent<UITransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<UITransformComponent>(FindComponent("Transform").lock());
	Transform->SetLocalPos(-60.f, -35.f, 0.f);

	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	// Kirby라는 이름의 텍스처를 사용할것이다
	Animation->SetTexture("StageIcon");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(100);

	//
	Animation->AddAnimation("StageIcon", "StageIcon", FVector2D(5.f, 22.f), FVector2D(118.f, 78.f), FVector2D(0.f, 0.f), 1, 1);
	Animation->ChangeState("StageIcon", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(0);

	Transform->UpdateMatrix();

	//
	
	mViewPort = ObjectViewPort::Bottom;

	return true;
}