#pragma once

#include "InhalableEnemyObject.h"

class BeamEnemy : public InhalableEnemyObject
{
public:
	bool Init();

	void PreRender(float DeltaTime) override;

	void EnemyMoving() override;
};

