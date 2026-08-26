#include "BeamWaveCenter.h"

#include "../Component/TransformComponent.h"
#include "../Component/AnimationComponent.h"

#include "../Component/ColliderAABB2D.h"

#include "BeamWaveProjectile.h"

#include "../Scene/Scene.h"
#include "../Asset/AssetManager.h"

bool BeamWaveCenter::Init()
{
	mObjectType = ObjectType::KirbyProjectile;

	CreateComponent<CTransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());
	Transform->SetLocalScale(0.75f, 0.75f, 1.f);

	CreateComponent<CColliderAABB2D>("Collider");
	auto Collider = std::dynamic_pointer_cast<CColliderAABB2D>(FindComponent("Collider").lock());
	Collider->UpdateTransform();
	mScene.lock()->AddCollider(Collider);

	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	// Kirby라는 이름의 텍스처를 사용할것이다
	Animation->SetTexture("BeamObject");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(10);
	
	// 1. 애니메이션을 추가한다
	Animation->AddAnimation("BeamObject", "Default", FVector2D(0.f, 0.f), FVector2D(1.f, 1.f), FVector2D(0.f, 0.f), 1, 1);
	Animation->ChangeState("Default", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(1);

	CreateChildObject<BeamWaveProjectile>("Projectile_0");
	std::dynamic_pointer_cast<CTransformComponent>(FindObject("Projectile_0").lock()->FindComponent("Transform").lock())->AddLocalPos(0.f, 7.f);
	CreateChildObject<BeamWaveProjectile>("Projectile_1");
	std::dynamic_pointer_cast<CTransformComponent>(FindObject("Projectile_1").lock()->FindComponent("Transform").lock())->AddLocalPos(0.f, -7.f);

	return true;
}

void BeamWaveCenter::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());
	Transform->AddLocalRotationZ(SpinSpeed * DeltaTime);

	std::dynamic_pointer_cast<CTransformComponent>(FindObject("Projectile_0").lock()->FindComponent("Transform").lock())->AddLocalRotationZ(-SpinSpeed * DeltaTime);
	std::dynamic_pointer_cast<CTransformComponent>(FindObject("Projectile_1").lock()->FindComponent("Transform").lock())->AddLocalRotationZ(-SpinSpeed * DeltaTime);
}

void BeamWaveCenter::Collision(float DeltaTime)
{
	auto Collider = std::dynamic_pointer_cast<CColliderAABB2D>(FindComponent("Collider").lock());
	if (!(Collider->GetCollisionObjList().back().lock()->GetColliderSurface() == EColliderSurface::Pass))
	{
		CSceneObject::Collision(DeltaTime);

		CAssetManager::GetInstance().GetEffectManager()->PlayEffect("BeamWaveCollision1", 0.3f, FVector3D(0.f, 0.f, 0.f), std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock()));
		CAssetManager::GetInstance().GetEffectManager()->PlayEffect("BeamWaveCollision2", 0.3f, FVector3D(0.f, 0.f, 0.f), std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock()));
		CAssetManager::GetInstance().GetEffectManager()->PlayEffect("BeamWaveCollision3", 0.3f, FVector3D(0.f, 0.f, 0.f), std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock()));
	
		Destroy();
	}
}

float BeamWaveCenter::GetDamage()
{
	return mDamage;
}
