#pragma once

#include "../Object/SceneObject.h"

class PauseObject : public CSceneObject
{
public:
	bool Init() override;

	// PauseScreen에서 이친구를 적당히 1 2 3 4 순서대로 정렬한다.
};

