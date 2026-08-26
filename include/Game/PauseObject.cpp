#include "PauseObject.h"

#include "../Component/AnimationComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderLine2D.h"
#include "../Component/MapColliderAABB2D.h"

#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"

bool PauseObject::Init()
{
	// Transform
	CreateComponent<CTransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());
	Transform->SetLocalScale(256.f, 192.f, 1.f);
	Transform->SwitchUsingTextureScale();
	
	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	
	Animation->SetTexture("PauseScreen");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(51);

	Animation->AddAnimation("Pause"+ mName, "Pause" + mName,FVector2D(0,0), FVector2D(1280.f, 960.f), FVector2D(0.f,0.f), 1, 1);
	Animation->ChangeState("Pause"+ mName, 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(0);

	return true;
}
