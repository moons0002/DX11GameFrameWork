#pragma once

#include "../Component/SceneComponent.h"

#include "KirbyStateComponent.h"
#include "KirbyObject.h"

class CTransformComponent;
class CColliderBase;

class KirbyDamage : public CSceneComponent
{
public:
	bool Init() override;
	void Collision(float DeltaTime) override;

protected:
	std::shared_ptr<CTransformComponent> mTransform;
	std::shared_ptr<CColliderBase> mCollision;
	std::shared_ptr<CSceneObject> mObject;
	std::shared_ptr<KirbyStateComponent> mKirbyState;
	std::shared_ptr<KirbyObject> mKirby;
};

