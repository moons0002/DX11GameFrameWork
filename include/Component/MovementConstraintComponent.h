#pragma once

#include "SceneComponent.h"

#include "TransformComponent.h"
#include "ColliderBase.h"

class MovementConstraintComponent : public CSceneComponent
{
public:
	bool Init() override;

	void Collision(float Deltatime) override;

protected:
	std::weak_ptr<CTransformComponent> mTransform;
	std::weak_ptr<CColliderBase> mCollision;
};

