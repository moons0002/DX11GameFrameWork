#pragma once

#include "../Component/SceneComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/ColliderBase.h"
#include "Door.h"

class DoorComponent : public CSceneComponent
{
protected:
	bool IsCheckingDoor;

	std::weak_ptr<CTransformComponent> Transform;
	std::weak_ptr<CColliderBase> Collider;
	std::shared_ptr<Door> mDoor;

public:
	bool Init() override;

	void Collision(float DeltaTime) override;

	void PreRender(float DeltaTime) override;

	void CheckDoor();
};

