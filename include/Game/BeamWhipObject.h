#pragma once

#include "../Object/SceneObject.h"

class BeamWhipObject : public CSceneObject
{
public:
	bool Init() override;

	void Update(float DeltaTime) override;

	void Collision(float DeltaTime) override;
};

