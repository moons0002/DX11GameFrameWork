#include "KirbyNotHp.h"

#include "../Component/AnimationComponent.h"
#include "../Component/UITransformComponent.h"

#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"

#include "KirbyObject.h"

bool KirbyNotHp::Init()
{
	// Transform
	CreateComponent<UITransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<UITransformComponent>(FindComponent("Transform").lock());

	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	// Kirby라는 이름의 텍스처를 사용할것이다
	Animation->SetTexture("KirbyHP");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(101);

	// 전체 체력바의 1/18
	Animation->AddAnimation("KirbyHp", "NotHp", FVector2D(92.f, 3.f), FVector2D(4.f, 10.f), FVector2D(0.f, 0.f), 1, 1);
	Animation->ChangeState("NotHp", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(0);

	Transform->UpdateMatrix();

	mViewPort = ObjectViewPort::Bottom;

	return true;
}

void KirbyNotHp::PreRender(float DeltaTime)
{
	CSceneObject::PreRender(DeltaTime);

	float Hp = std::dynamic_pointer_cast<KirbyObject>(mScene.lock()->FindObject("Kirby").lock())->GetHp();
	if (Hp <= 0) Hp = 0;
	float NotHpRatio = (100.f - Hp) * (18.f / 100.f);

	auto Transform = std::dynamic_pointer_cast<UITransformComponent>(FindComponent("Transform").lock());

	Transform->SetLocalPos(36 - NotHpRatio * 2.f, 0.f, 0.f);
	Transform->SetLocalScale(NotHpRatio, 1.f, 1.f);

	Transform->UpdateMatrix();
}