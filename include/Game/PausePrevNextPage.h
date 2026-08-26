#pragma once

#include "../Object/SceneObject.h"

class PausePrevNextPage : public CSceneObject
{
public:
	bool Init() override;

	void Update(float DeltaTime) override;

protected:
	static int count;
	int mCount;

	float mTime = 0.1f;
	float mTimeSum = 0.f;

	int mDirection;

	float mSpeed = 30.f;
};