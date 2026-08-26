#include "Stage_1_1.h"

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
#include "Stage_1_1_0.h"

bool Stage_1_1::Init()
{
	mObjectType = ObjectType::Map;

	// Transform
	CreateComponent<CTransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());

	// Collider
	// Ground
	CreateComponent<MapColliderAABB2D>("Ground-0");
	auto Collider = std::dynamic_pointer_cast<MapColliderAABB2D>(FindComponent("Ground-0").lock());
	Collider->SetCenter(FVector3D(Stage_1_1_Left + 0.f + 84.f, Stage_1_1_Top - 188.f, 0.f));
	Collider->SetSize(FVector3D(164.f, 45.f, 0.f));
	Collider->SetColliderSurface(EColliderSurface::Ground);
	Collider->UpdateTransform();
	mScene.lock()->AddCollider(Collider);

	CreateComponent<MapColliderAABB2D>("Ground-1");
	Collider = std::dynamic_pointer_cast<MapColliderAABB2D>(FindComponent("Ground-1").lock());
	Collider->SetCenter(FVector3D(Stage_1_1_Left + 219.f, Stage_1_1_Top - 163.f, 0.f));
	Collider->SetSize(FVector3D(98.f, 45.f, 0.f));
	Collider->SetColliderSurface(EColliderSurface::Ground);
	Collider->UpdateTransform();
	mScene.lock()->AddCollider(Collider);

	CreateComponent<MapColliderAABB2D>("Ground-2");
	Collider = std::dynamic_pointer_cast<MapColliderAABB2D>(FindComponent("Ground-2").lock());
	Collider->SetCenter(FVector3D(Stage_1_1_Left + 264.f + 24.f, Stage_1_1_Top - 111.f, 0.f));
	Collider->SetSize(FVector3D(48.f, 85.f, 0.f));
	Collider->SetColliderSurface(EColliderSurface::Ground);
	Collider->UpdateTransform();
	mScene.lock()->AddCollider(Collider);

	CreateComponent<MapColliderAABB2D>("Ground-3");
	Collider = std::dynamic_pointer_cast<MapColliderAABB2D>(FindComponent("Ground-3").lock());
	Collider->SetCenter(FVector3D(Stage_1_1_Left + 384.f, Stage_1_1_Top - 163.f, 0.f));
	Collider->SetSize(FVector3D(146.f, 45.f, 0.f));
	Collider->SetColliderSurface(EColliderSurface::Ground);
	Collider->UpdateTransform();
	mScene.lock()->AddCollider(Collider);

	//
	CreateComponent<MapColliderAABB2D>("Left");
	Collider = std::dynamic_pointer_cast<MapColliderAABB2D>(FindComponent("Left").lock());
	Collider->SetCenter(FVector3D(Stage_1_1_Left - 10.f, 0.f, 0.f));
	Collider->SetSize(FVector3D(20.f, Stage_1_1_Top * 2.f, 0.f));
	Collider->SetColliderSurface(EColliderSurface::Ground);
	Collider->UpdateTransform();
	mScene.lock()->AddCollider(Collider);

	//
	CreateComponent<MapColliderAABB2D>("Right");
	Collider = std::dynamic_pointer_cast<MapColliderAABB2D>(FindComponent("Right").lock());
	Collider->SetCenter(FVector3D(-Stage_1_1_Left + 10.f, 0.f, 0.f));
	Collider->SetSize(FVector3D(20.f, Stage_1_1_Top * 2.f, 0.f));
	Collider->SetColliderSurface(EColliderSurface::Ground);
	Collider->UpdateTransform();
	mScene.lock()->AddCollider(Collider);

	//
	CreateComponent<MapColliderAABB2D>("Top");
	Collider = std::dynamic_pointer_cast<MapColliderAABB2D>(FindComponent("Top").lock());
	Collider->SetCenter(FVector3D(0.f, Stage_1_1_Top + 10.f, 0.f));
	Collider->SetSize(FVector3D(-Stage_1_1_Left * 2.f, 20.f, 0.f));
	Collider->SetColliderSurface(EColliderSurface::Ground);
	Collider->UpdateTransform();
	mScene.lock()->AddCollider(Collider);

	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	
	Animation->SetTexture("Map");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(0);

	Animation->AddAnimation("Stage_1_1", "Stage_1_1",FVector2D(0,0), FVector2D(888.f, 216.f), FVector2D(0.f,0.f), 1, 1);
	Animation->ChangeState("Stage_1_1", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Loop);
	Animation->SetSpeed(0);

	// Door
	CreateChildObject<Door>("Door_0");
	auto Door_0 = std::dynamic_pointer_cast<Door>(FindObject("Door_0").lock());
	Door_0->SetToPosition(FVector2D(Stage_1_1_0_Left + 155.f, Stage_1_1_0_Top - 96.f));
	Door_0->SetToStage("Stage_1_1_0");
	std::dynamic_pointer_cast<MapColliderAABB2D>(Door_0->FindComponent("Collider").lock())->SetCenter(FVector3D(Stage_1_1_Left + 396.f, Stage_1_1_Top - 125.f, 0.f));

	return true;
}
