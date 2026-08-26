#pragma once

#include "../Object/SceneObject.h"

class KirbyLifeCount : public CSceneObject
{
public:
	bool Init() override;

	void PreRender(float DeltaTiem) override;

protected:
	static int DigitCount;

	int mDigit = 0;
};