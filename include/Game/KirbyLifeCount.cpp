#include "KirbyLifeCount.h"

#include "../Component/AnimationComponent.h"
#include "../Component/UITransformComponent.h"

#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"

#include "KirbyObject.h"

int KirbyLifeCount::DigitCount = -1;

bool KirbyLifeCount::Init()
{
	++DigitCount;
	mDigit = DigitCount;
	CreateComponent<UITransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<UITransformComponent>(FindComponent("Transform").lock());
	Transform->SetLocalPos(-54.f - (mDigit * 10), 39.f, 0.f);

	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	// Kirby라는 이름의 텍스처를 사용할것이다
	Animation->SetTexture("GeneralRips");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(100);

	//
	Animation->AddAnimation("GeneralRips", "KirbyLifeCount", FVector2D(316.f, 338.f), FVector2D(9.f, 10.f), FVector2D(0.f, 0.f), 10, 1);
	Animation->ChangeState("KirbyLifeCount", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(0);

	Transform->UpdateMatrix();

	//
	
	mViewPort = ObjectViewPort::Bottom;

	return true;
}

void KirbyLifeCount::PreRender(float DeltaTiem)
{
	int Life = std::dynamic_pointer_cast<KirbyObject>(mScene.lock()->FindObject("Kirby").lock())->GetLife();
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());

	Animation->ChangeFrame((Life % (int)(std::pow(10.f, (mDigit + 1)))) / (int)(std::pow(10.f, mDigit)));
}