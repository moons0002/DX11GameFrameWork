#include "Stage_1_1_0.h"

#include "../Component/AnimationComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderLine2D.h"
#include "../Component/MapColliderAABB2D.h"

#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"

#include "Door.h"
#include "Stage_1_1.h"

bool Stage_1_1_0::Init()
{
	mObjectType = ObjectType::Map;

	// Transform
	CreateComponent<CTransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());

	CreateComponent<MapColliderAABB2D>("Collider_1");
	auto Collider = std::dynamic_pointer_cast<MapColliderAABB2D>(FindComponent("Collider_1").lock());
	Collider->SetCenter(FVector3D(Stage_1_1_0_Left + 125.f, Stage_1_1_0_Top - 11.f, 0.f));
	Collider->SetSize(FVector3D(215.f, 24.f, 0.f));
	Collider->SetColliderSurface(EColliderSurface::Ground);
	Collider->UpdateTransform();
	mScene.lock()->AddCollider(Collider);

	CreateComponent<MapColliderAABB2D>("Collider_2");
	Collider = std::dynamic_pointer_cast<MapColliderAABB2D>(FindComponent("Collider_2").lock());
	Collider->SetCenter(FVector3D(Stage_1_1_0_Left + 36.f, Stage_1_1_0_Top - 88.f, 0.f));
	Collider->SetSize(FVector3D(24.f, 169.f, 0.f));
	Collider->SetColliderSurface(EColliderSurface::Ground);
	Collider->UpdateTransform();
	mScene.lock()->AddCollider(Collider);

	CreateComponent<MapColliderAABB2D>("Collider_3");
	Collider = std::dynamic_pointer_cast<MapColliderAABB2D>(FindComponent("Collider_3").lock());
	Collider->SetCenter(FVector3D(Stage_1_1_0_Left + 125.f, Stage_1_1_0_Top - 178.f, 0.f));
	Collider->SetSize(FVector3D(215.f, 24.f, 0.f));
	Collider->SetColliderSurface(EColliderSurface::Ground);
	Collider->UpdateTransform();
	mScene.lock()->AddCollider(Collider);

	CreateComponent<MapColliderAABB2D>("Collider_4");
	Collider = std::dynamic_pointer_cast<MapColliderAABB2D>(FindComponent("Collider_4").lock());
	Collider->SetCenter(FVector3D(Stage_1_1_0_Left + 230.f, Stage_1_1_0_Top - 88.f, 0.f));
	Collider->SetSize(FVector3D(24.f, 169.f, 0.f));
	Collider->SetColliderSurface(EColliderSurface::Ground);
	Collider->UpdateTransform();
	mScene.lock()->AddCollider(Collider);

	CreateComponent<MapColliderAABB2D>("Collider_5");
	Collider = std::dynamic_pointer_cast<MapColliderAABB2D>(FindComponent("Collider_5").lock());
	Collider->SetCenter(FVector3D(Stage_1_1_0_Left + 156.f, Stage_1_1_0_Top - 123.f, 0.f));
	Collider->SetSize(FVector3D(68.f, 10.f, 0.f));
	Collider->SetColliderSurface(EColliderSurface::Ground);
	Collider->UpdateTransform();
	mScene.lock()->AddCollider(Collider);

	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	
	Animation->SetTexture("Map");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(0);

	Animation->AddAnimation("Stage_1_1_0", "Stage_1_1_0",FVector2D(0,0), FVector2D(264.f, 216.f), FVector2D(0.f,0.f), 1, 1);
	Animation->ChangeState("Stage_1_1_0", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(0);

	// Door
	CreateChildObject<Door>("Door_0");
	auto Door_0 = std::dynamic_pointer_cast<Door>(FindObject("Door_0").lock());
	Door_0->SetToPosition(FVector2D(Stage_1_1_Left + 396.f, Stage_1_1_Top - 125.f));
	Door_0->SetToStage("Stage_1_1");
	std::dynamic_pointer_cast<MapColliderAABB2D>(Door_0->FindComponent("Collider").lock())->SetCenter(FVector3D(Stage_1_1_0_Left + 155.f, Stage_1_1_0_Top - 96.f, 0.f));

	return true;
}