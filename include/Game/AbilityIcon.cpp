#include "AbilityIcon.h"

#include "../Component/AnimationComponent.h"
#include "../Component/UITransformComponent.h"

#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"

#include "KirbyObject.h"

bool AbilityIcon::Init()
{
	CreateComponent<UITransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<UITransformComponent>(FindComponent("Transform").lock());
	Transform->SetLocalPos(-108.5f, 76.5f, 0.f);

	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	Animation->SetTexture("GeneralRips");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(100);

	//
	Animation->AddAnimation("GeneralRips", "AbilityIcon", FVector2D(0.f, 25.f), FVector2D(33.f, 33.f), FVector2D(0.f, 0.f), 10, 7);
	Animation->ChangeState("AbilityIcon", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(0);

	Transform->UpdateMatrix();

	//
	
	mViewPort = ObjectViewPort::Bottom;

	return true;
}

void AbilityIcon::PreRender(float DeltaTiem)
{
	EKirbyAbility Ability = std::dynamic_pointer_cast<KirbyObject>(mScene.lock()->FindObject("Kirby").lock())->GetAbility();
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());

	switch (Ability)
	{
	case EKirbyAbility::None:
		Animation->ChangeFrame(0);
		break;
	case EKirbyAbility::Beam:
		Animation->ChangeFrame(22);
		break;
	default:
		break;
	}
}
