#include "ScoreCount.h"

#include "../Component/AnimationComponent.h"
#include "../Component/UITransformComponent.h"

#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"

#include "StageScene.h"

int ScoreCount::DigitCount = -1;

bool ScoreCount::Init()
{
	++DigitCount;
	mDigit = DigitCount;
	CreateComponent<UITransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<UITransformComponent>(FindComponent("Transform").lock());
	Transform->SetWorldPos(88.f - (mDigit * 10), 39.f, 0.f);

	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	// Kirby라는 이름의 텍스처를 사용할것이다
	Animation->SetTexture("GeneralRips");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(100);

	//
	Animation->AddAnimation("GeneralRips", "LifeCount", FVector2D(316.f, 338.f), FVector2D(9.f, 10.f), FVector2D(0.f, 0.f), 10, 1);
	Animation->ChangeState("LifeCount", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(0);

	Transform->UpdateMatrix();

	//
	
	mViewPort = ObjectViewPort::Bottom;

	if (DigitCount < 6) CreateChildObject<ScoreCount>("ScoreCount");

	return true;
}

void ScoreCount::PreRender(float DeltaTime)
{
	CSceneObject::PreRender(DeltaTime);
	int Score = std::dynamic_pointer_cast<StageScene>(mScene.lock())->GetScore();
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());

	Animation->ChangeFrame((Score % (int)(std::pow(10.f, (mDigit + 1)))) / (int)(std::pow(10.f, mDigit)));
}
