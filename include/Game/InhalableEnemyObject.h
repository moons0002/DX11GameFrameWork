#pragma once

#include "EnemyObject.h"

class CTransformComponent;

enum EInhalableEnemyType
{
	None,
	Beam
};

class InhalableEnemyObject : public CEnemyObject
{
protected:
	EInhalableEnemyType mInhalableEnemyType = EInhalableEnemyType::None;

	// 흡수가 시작되었는가
	bool InhalingStart = false;
	// 흡수 중인가
	bool IsInhaled = false;
	// 흡수 속도
	float InhaleSpeed = 200.f;
	// 커비한테 이동 중인가
	bool IsInhalingEnd = false;

	// 커비 위치
	std::weak_ptr<CTransformComponent> KirbyTransform;
	std::weak_ptr<CTransformComponent> MyTransform;

public:
	EInhalableEnemyType GetInhalableEnemyType();

public:
	bool Init() override;

	void Update(float DeltaTime) override;
	
	void StartInhaled();
	void StopInhaled();
};

