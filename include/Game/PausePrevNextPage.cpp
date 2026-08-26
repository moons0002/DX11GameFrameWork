#include "PausePrevNextPage.h"

#include "../Component/AnimationComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderLine2D.h"
#include "../Component/MapColliderAABB2D.h"

#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"

int PausePrevNextPage::count = 0.f;

bool PausePrevNextPage::Init()
{
	mCount = count;
	// Transform
	CreateComponent<CTransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());
	Transform->SetLocalScale(20.f, 120.f, 1.f);
	Transform->SwitchUsingTextureScale();
	if (mCount == 0)
	{
		Transform->SetVelocityX(mSpeed);
		mDirection = 1;
	}
	else // mCount == 1;
	{
		Transform->SetVelocityX(-mSpeed);
		mDirection = -1;
	}

	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	
	Animation->SetTexture("PauseScreen");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(60);

	Animation->AddAnimation("PrevNextPage", "PrevNextPage",FVector2D(100.f * count, 0), FVector2D(100.f, 600.f), FVector2D(0.f,0.f), 1, 1);
	Animation->ChangeState("PrevNextPage");
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(0);

	++count;
	count %= 2;

	return true;
}

void PausePrevNextPage::Update(float DeltaTime)
{
	mTimeSum += DeltaTime;
	if (mTime <= mTimeSum)
	{
		mTimeSum -= mTime;
		auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());
		
		mDirection *= -1;
		Transform->SetVelocityX(mSpeed * mDirection);

		if (mCount == 0 && mDirection == 1)
		{
			Transform->SetLocalPos(-120.f, 0.f, 0.f);
		}
		else if (mCount == 1 && mDirection == -1)
		{
			Transform->SetLocalPos(120.f, 0.f, 0.f);
		}
	}
}