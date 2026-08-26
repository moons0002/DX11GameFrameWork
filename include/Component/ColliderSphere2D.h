#pragma once

#include "ColliderBase.h"

class CColliderAABB2D;
class CColliderOBB2D;
class CColliderLine2D;

class CColliderSphere2D : public CColliderBase
{
public:
	CColliderSphere2D();
	~CColliderSphere2D();

protected:
	float mRadius = 0.f;

public:
	float GetRadius()
	{
		return mRadius;
	}

	void SetRadius(float radius)
	{
		mRadius = radius;
	}

public:
	bool Init() override;

	bool CheckCollision(std::shared_ptr<CColliderBase> collider, float DeltaTime) override;

	bool CollisionSphere2DtoSphere2D(std::shared_ptr<CColliderSphere2D> collider);

	bool CollisionSphere2DtoAABB2D(std::shared_ptr<CColliderAABB2D> collider);

	bool CollisionSphere2DtoOBB2D(std::shared_ptr<CColliderOBB2D> collider);

	bool CollisionSphere2DtoLine2D(std::shared_ptr<CColliderLine2D> collider);

	void UpdateTransform() override;
};