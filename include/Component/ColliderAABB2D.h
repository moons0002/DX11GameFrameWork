#pragma once

#include "ColliderBase.h"

class CColliderSphere2D;
class CColliderOBB2D;
class CColliderLine2D;

class CColliderAABB2D : public CColliderBase
{
public:
	CColliderAABB2D();
	~CColliderAABB2D();
	
public:
	bool Init() override;

	bool CheckCollision(std::shared_ptr<CColliderBase> collider, float DeltaTime) override;

	bool CollisionAABB2DtoAABB2D(std::shared_ptr<CColliderAABB2D> collider);

	bool CollisionAABB2DtoSphere2D(std::shared_ptr<CColliderSphere2D> collider);

	bool CollisionAABB2DtoOBB2D(std::shared_ptr<CColliderOBB2D> collider);

	bool CollisionAABB2DtoLine2D(std::shared_ptr<CColliderLine2D> collider);
};