#pragma once

#include "SceneComponent.h"

#include "../Game/KirbyStateComponent.h"
#include "TransformComponent.h"

class GravityComponent : public CSceneComponent
{
public:
	bool Init() override;

	void PreUpdate(float DeltaTime) override;

protected:
	std::weak_ptr<CTransformComponent> mTransform;
	
	std::weak_ptr<KirbyStateComponent> mKirby;
};

