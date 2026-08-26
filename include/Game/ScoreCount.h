#pragma once

#include "../Object/SceneObject.h"

class ScoreCount : public CSceneObject
{
public:
	bool Init() override;

	void PreRender(float DeltaTime) override;

protected:
	static int DigitCount;

	int mDigit = 0;
};

