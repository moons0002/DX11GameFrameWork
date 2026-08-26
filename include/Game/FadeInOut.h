#pragma once

#include "../Object/SceneObject.h"
#include "../Component/AnimationComponent.h"

class FadeInOut : public CSceneObject
{
public:
	bool Init() override;

	void PreRender(float DeltaTime) override;

public:
	// 지정된 강도만큼 완전히 어두워짐
	void FadeOut(float Intensity);
	// 지정된 강도만큼 완전히 밝아짐
	void FadeIn(float Intensity);

protected:
	float mIntensity = 0.f;

	bool IsFadeOut = false;
	bool IsFadeIn = false;

	std::shared_ptr<CAnimationComponent> Animation;
};

