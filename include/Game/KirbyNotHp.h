#pragma once

#include "../Object/SceneObject.h"

class KirbyNotHp : public CSceneObject
{
public:
	bool Init() override;

	void PreRender(float DeltaTime) override;
};

