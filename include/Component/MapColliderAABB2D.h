#pragma once

#include "ColliderAABB2D.h"

class MapColliderAABB2D : public CColliderAABB2D
{
public:
	void UpdateTransform() override;

};

