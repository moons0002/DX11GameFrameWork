#pragma once

#include "../Component/SceneComponent.h"
#include "InhalableEnemyObject.h"

class CEnemyObject;

class CInhaleComponent : public CSceneComponent
{
protected:
	FVector2D mSmallSize = FVector2D(80.f, 24.f);

	std::weak_ptr<CEnemyObject> mInhaleEnemy;

public:
	void StartInhale(bool IsLookingRight);
	void StopInhale();

	void CompleteInhale(EInhalableEnemyType EnemyType);
};