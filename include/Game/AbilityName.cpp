#include "AbilityName.h"

#include "../Component/AnimationComponent.h"
#include "../Component/UITransformComponent.h"

#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"

#include "KirbyObject.h"

bool AbilityName::Init()
{
	CreateComponent<UITransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<UITransformComponent>(FindComponent("Transform").lock());
	Transform->SetLocalPos(-48.f, 65.f, 0.f);

	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	Animation->SetTexture("GeneralRips");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(100);

	//
	Animation->AddAnimation("GeneralRips", "AbilityName", FVector2D(0.f, 276.f), FVector2D(72.f, 15.f), FVector2D(0.f, 0.f), 4, 15);
	Animation->ChangeState("AbilityName", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(0);
	Animation->SetPivot(36.f, 0.f);

	Transform->UpdateMatrix();

	//
	
	mViewPort = ObjectViewPort::Bottom;

	return true;
}

void AbilityName::PreRender(float DeltaTiem)
{
	EKirbyAbility Ability = std::dynamic_pointer_cast<KirbyObject>(mScene.lock()->FindObject("Kirby").lock())->GetAbility();
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());

	switch (Ability)
	{
	case EKirbyAbility::None:
		Animation->ChangeFrame(0);
		break;
	case EKirbyAbility::Beam:
		Animation->ChangeFrame(18);
		break;
	default:
		break;
	}
}
