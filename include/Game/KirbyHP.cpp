#include "KirbyHP.h"

#include "../Component/AnimationComponent.h"
#include "../Component/UITransformComponent.h"

#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"

#include "KirbyNotHp.h"
#include "KirbyChangeHP.h"

bool KirbyHP::Init()
{
	// Transform
	CreateComponent<UITransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<UITransformComponent>(FindComponent("Transform").lock());
	Transform->SetLocalPos(-46.f, 83.5f, 0.f);

	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	// Kirby라는 이름의 텍스처를 사용할것이다
	Animation->SetTexture("KirbyHP");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(100);

	//
	Animation->AddAnimation("KirbyHp", "Hp", FVector2D(0.f, 0.f), FVector2D(78.f, 16.f), FVector2D(0.f, 0.f), 1, 1);
	Animation->ChangeState("Hp", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(0);

	Transform->UpdateMatrix();

	//

	CreateChildObject<KirbyNotHp>("KirbyNotHp");
	CreateChildObject<KirbyChangeHP>("KirbyChangeHp");

	//
	
	mViewPort = ObjectViewPort::Bottom;

	return true;
}