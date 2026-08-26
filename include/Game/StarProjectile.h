#pragma once

#include "../Object/SceneObject.h"

class StarProjectile : public CSceneObject
{
public:
	bool Init() override;

	void Update(float DeltaTime) override;

	void Collision(float DeltaTime) override;

protected:
	float SpinSpeed = 1200.f;

	bool IsCollision = false;

	float TimeSum = 0.f;

	float mDamage = 0.f;

public:
	float GetDamage();
	
};