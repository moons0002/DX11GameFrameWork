#pragma once

#include "../Object/SceneObject.h"

class KirbyChangeHP : public CSceneObject
{
public:
	bool Init() override;

	void PreRender(float DeltaTime) override;

protected:
	float PrevHp = 100.f;

	float Scale = 0.f;

	float HpDecreaseSpeed = 10.f;

	bool IsChangingHp = false;
};

