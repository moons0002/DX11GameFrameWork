#include "StarProjectile.h"

#include "../Component/AnimationComponent.h"
#include "../Component/TransformComponent.h"

#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"

#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"

bool StarProjectile::Init()
{
	mObjectType = ObjectType::KirbyProjectile;

	CreateComponent<CTransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());

	CreateComponent<CColliderAABB2D>("Collider");
	auto Collider = std::dynamic_pointer_cast<CColliderAABB2D>(FindComponent("Collider").lock());
	Collider->UpdateTransform();
	mScene.lock()->AddCollider(Collider);

	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	Animation->SetTexture("Projectile");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(10);
	
	// 1. 애니메이션을 추가한다
	Animation->AddAnimation("Star", "Star", FVector2D(0.f, 0.f), FVector2D(24.f, 24.f), FVector2D(0.f, 0.f), 1, 1);
	Animation->ChangeState("Star", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(1);

	return true;
}

void StarProjectile::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());
	Transform->AddLocalRotationZ(SpinSpeed * DeltaTime);
}

void StarProjectile::Collision(float DeltaTime)
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

float StarProjectile::GetDamage()
{
	return mDamage;
}