#include "BottomScreen.h"

#include "../Component/AnimationComponent.h"
#include "../Component/UITransformComponent.h"

#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"

bool BottomScreen::Init()
{
	// Transform
	CreateComponent<UITransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<UITransformComponent>(FindComponent("Transform").lock());
	Transform->SetLocalScale(256.f, 192.f, 1.f);

	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	Animation->SetTexture("BottomScreen");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(99);

	//
	Animation->AddAnimation("BottomScreen", "BottomScreen", FVector2D(0.f, 0.f), FVector2D(1280.f, 960.f), FVector2D(0.f, 0.f), 1, 1);
	Animation->ChangeState("BottomScreen", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(0);

	Transform->SwitchUsingTextureScale();
	Transform->UpdateMatrix();

	//
	
	mViewPort = ObjectViewPort::Bottom;

	return true;
}
