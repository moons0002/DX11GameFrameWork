#pragma once

#include "InhalableEnemyObject.h"

class BrontoBurtEnemy : public InhalableEnemyObject
{
protected:

public:
	bool Init();

	void PreRender(float DeltaTime) override;

	float FlyTime = 0.7f;
	float FlyStartTime = 0.f;

	bool IsUp = true;
	bool IsRight = true;

public:
	void EnemyMoving() override;
};