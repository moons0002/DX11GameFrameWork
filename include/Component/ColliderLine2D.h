#pragma once

#include "ColliderBase.h"

class CColliderAABB2D;
class CColliderSphere2D;
class CColliderOBB2D;

class CColliderLine2D : public CColliderBase
{

public:
	FVector2D mPoint_0;
	FVector2D mPoint_1;

public:
	bool Init();

	bool CheckCollision(std::shared_ptr<CColliderBase> collider, float DeltaTime);

	bool CollisionLine2DtoAABB2D(std::shared_ptr<CColliderAABB2D> collider);
	bool CollisionLine2DtoSphere2D(std::shared_ptr<CColliderSphere2D> collider);
	bool CollisionLine2DtoOBB2D(std::shared_ptr<CColliderOBB2D> collider);
	bool CollisionLine2DtoLine2D(std::shared_ptr<CColliderLine2D> collider);

public:
	void SetPoint_0(float x, float y);
	void SetPoint_1(float x, float y);

	FVector2D GetPoint_0();
	FVector2D GetPoint_1();

	void UpdateTransform() override;
};

