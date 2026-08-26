#pragma once

#include "ColliderBase.h"

class CColliderAABB2D;
class CColliderSphere2D;
class CColliderLine2D;

struct FOBB2D
{
	FVector2D v0;
	FVector2D v1;

	FVector2D axis0 = {1.f, 0.f};
	FVector2D axis1 = {0.f, 1.f};
};

class CColliderOBB2D : public CColliderBase
{
public:
	CColliderOBB2D();
	~CColliderOBB2D();

protected:
	FOBB2D mOBB;

	FVector3D mRot;

public:
	bool Init() override;

	bool CheckCollision(std::shared_ptr<CColliderBase> collider, float DeltaTime) override;

	FOBB2D& GetOBB()
	{
		return mOBB;
	}

	FVector3D& GetRot()
	{
		return mRot;
	}

	bool CollisionOBB2DtoOBB2D(std::shared_ptr<CColliderOBB2D> collider);

	bool CollisionOBB2DtoAABB2D(std::shared_ptr<CColliderAABB2D> collider);

	bool CollisionOBB2DtoSphere2D(std::shared_ptr<CColliderSphere2D> collider);

	bool CollisionOBB2DtoLine2D(std::shared_ptr<CColliderLine2D> collider);

	void UpdateTransform() override;
};