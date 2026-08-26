#pragma once

#include "../Object/SceneObject.h"

class AbilityName : public CSceneObject
{
public:
	bool Init() override;

	void PreRender(float DeltaTiem) override;
};

