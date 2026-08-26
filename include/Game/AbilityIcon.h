#pragma once

#include "../Object/SceneObject.h"

class AbilityIcon : public CSceneObject
{
public:
	bool Init() override;

	void PreRender(float DeltaTiem) override;
};

