#include "FadeInOut.h"

#include "../Component/AnimationComponent.h"
#include "../Component/UITransformComponent.h"

bool FadeInOut::Init()
{
	CreateComponent<UITransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<UITransformComponent>(FindComponent("Transform").lock());
	Transform->SetLocalScale(1280.f, 1280.f, 1.f);

	CreateComponent<CAnimationComponent>("Animation");
	Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	Animation->SetTexture("Color");
	Animation->SetOpacity(0, 0.f);
	Animation->SetSortingOrder(100);

	Animation->AddAnimation("Black", "Black", FVector2D(0.f, 0.f), FVector2D(1.f, 1.f), FVector2D(0.f, 0.f), 1, 1);
	Animation->ChangeState("Black", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(0);

	Transform->UpdateMatrix();
	//

	return true;
}

void FadeInOut::PreRender(float DeltaTime)
{
	// 검은색 오브젝트를 보여줄것이냐 말것이냐
	if (IsFadeIn)
	{
		// 밝아지기
		Animation->AddOpacity(0, -DeltaTime * mIntensity);

		if (Animation->GetOpacity(0) <= 0.f)
		{
			IsFadeIn = false;
		}
	}
	else if (IsFadeOut)
	{
		// 어두워지기
		Animation->AddOpacity(0, DeltaTime * mIntensity);

		if (Animation->GetOpacity(0) >= 1.f)
		{
			IsFadeOut = false;
		}
	}
}

void FadeInOut::FadeOut(float Intensity)
{
	mIntensity = Intensity * 5.f;
	IsFadeOut = true;
	IsFadeIn = false;
}

void FadeInOut::FadeIn(float Intensity)
{
	mIntensity = Intensity * 5.f;
	IsFadeIn = true;
	IsFadeOut = false;
}
