#pragma once

#include "../Component/SceneComponent.h"

class UITransformComponent;

class BackGroundMovementComponent : public CSceneComponent
{
public:
	BackGroundMovementComponent();
	virtual ~BackGroundMovementComponent();

public:
	std::weak_ptr<UITransformComponent> mTransformComponent;

protected:
	float mSpeed = 0.2f;

	FVector3D* KirbyPosition = nullptr;

public:
	bool Init() override;

	void Update(float DeltaTime) override;
};

