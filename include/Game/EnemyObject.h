#pragma once

#include "../Object/SceneObject.h"

class CTransformComponent;
class CAnimationComponent;

enum EnemyType
{
	Inhalable
};

class CEnemyObject : public CSceneObject
{
public:
	EnemyType mEnemyType;

	float mHP = 1.f;
	float mDamage = 0.f;

	// 현재 시간
    float Time = 0;
    // 이전 시간
    float PrevTime = 0;

	float DestroyTime = 0.2f;
	float DestroyStartTime = 0.f;
public:
	bool Init() override;

	void Update(float DeltaTime) override;

	void Collision(float DeltaTime) override;

	virtual void EnemyMoving();

public:

	EnemyType GetEnemyType()
	{
		return mEnemyType;
	}

	float GetDamage()
	{
		return mDamage;
	}

	void AddHp(float Hp);
};

