#include "ColliderLine2D.h"

#include "../Object/SceneObject.h"

#include "ColliderAABB2D.h"
#include "ColliderSphere2D.h"
#include "ColliderOBB2D.h"

#include "CollisionCheck.h"

bool CColliderLine2D::Init()
{
	if (!CColliderBase::Init())
		return false;

	mColliderType = EColliderType::Collider2D;
	mColliderShape = EColliderShape::Line2D;

	return true;
}

bool CColliderLine2D::CheckCollision(std::shared_ptr<CColliderBase> collider, float DeltaTime)
{
	if (collider->GetColliderType() == EColliderType::Collider3D) return false;
	
	switch(collider->GetColliderShape())
	{
	case EColliderShape::AABB2D:
		if (CollisionLine2DtoAABB2D(std::dynamic_pointer_cast<CColliderAABB2D>(collider)))
		{
			return true;
		}
		break;
	case EColliderShape::Sphere2D:
		if (CollisionLine2DtoSphere2D(std::dynamic_pointer_cast<CColliderSphere2D>(collider)))
		{
			return true;
		}
		break;
	case EColliderShape::OBB2D:
		if (CollisionLine2DtoOBB2D(std::dynamic_pointer_cast<CColliderOBB2D>(collider)))
		{
			return true;
		}
		break;
	case EColliderShape::Line2D:
		if (CollisionLine2DtoLine2D(std::dynamic_pointer_cast<CColliderLine2D>(collider)))
		{
			return true;
		}
	default:
		break;
	}
	return false;
}

bool CColliderLine2D::CollisionLine2DtoAABB2D(std::shared_ptr<CColliderAABB2D> collider)
{
	FVector2D Dir = mPoint_0 - mPoint_1;

	float a = (Dir.y) / (Dir.x);
	float b = a * mPoint_0.x + mPoint_0.y;

	FVector2D Max = {collider->GetMax().x, collider->GetMax().y};
	FVector2D Min = {collider->GetMin().x, collider->GetMin().y};

	if ( !((mPoint_0.y > Max.y && mPoint_1.y > Max.y) || (mPoint_0.y < Min.y && mPoint_1.y < Min.y)))
	{
		float x_t = (Max.y - b) / a;
		if (Min.x <= x_t && x_t <= Max.x)
		{
			return true;
		}
		x_t = (Min.y - b) / a;
		if (Min.x <= x_t && x_t <= Max.x)
		{
			return true;
		}
	}

	if ( !((mPoint_0.x > Max.x && mPoint_1.x > Max.x) || (mPoint_0.x < Min.x && mPoint_1.x < Min.x)))
	{
		float y_t = a * Max.x + b;
		if (Min.y <= y_t && y_t <= Max.y)
		{
			return true;
		}
		y_t = a * Min.x + b;
		if (Min.y <= y_t && y_t <= Max.y)
		{
			return true;
		}
	}
	return false;
}

bool CColliderLine2D::CollisionLine2DtoSphere2D(std::shared_ptr<CColliderSphere2D> collider)
{
	FVector2D Center = FVector2D(collider->GetCenter().x, collider->GetCenter().y);

	FVector2D v = mPoint_1 - mPoint_0;
	FVector2D w = Center - mPoint_0;

	float t = v.Dot(w) / v.Dot(v);

	if (t < 0) t = 0;
	else if (t > 1) t = 1;

	FVector2D p = mPoint_0 + (mPoint_1 - mPoint_0) * t;

	if (p.Distance(Center) > collider->GetRadius())
		return false;

	return true;
}

bool CColliderLine2D::CollisionLine2DtoOBB2D(std::shared_ptr<CColliderOBB2D> collider)
{
	FVector3D Rot = collider->GetRot();

	FVector3D p0 = {mPoint_0.x, mPoint_0.y, 0};
	p0.Rotation(-Rot);
 	FVector3D p1 = {mPoint_1.x, mPoint_1.y, 0};
	p1.Rotation(-Rot);

	FVector2D Dir = {p0.x - p1.x, p0.y - p1.y};

	float a = (Dir.y) / (Dir.x);
	float b = a * p0.x + p0.y;

	FVector2D Max = {collider->GetMax().x, collider->GetMax().y};
	FVector2D Min = {collider->GetMin().x, collider->GetMin().y};

	if ( !((mPoint_0.y > Max.y && mPoint_1.y > Max.y) || (mPoint_0.y < Min.y && mPoint_1.y < Min.y)))
	{
		float x_t = (Max.y - b) / a;
		if (Min.x <= x_t && x_t <= Max.x)
		{
			return true;
		}
		x_t = (Min.y - b) / a;
		if (Min.x <= x_t && x_t <= Max.x)
		{
			return true;
		}
	}

	if ( !((mPoint_0.x > Max.x && mPoint_1.x > Max.x) || (mPoint_0.x < Min.x && mPoint_1.x < Min.x)))
	{
		float y_t = a * Max.x + b;
		if (Min.y <= y_t && y_t <= Max.y)
		{
			return true;
		}
		y_t = a * Min.x + b;
		if (Min.y <= y_t && y_t <= Max.y)
		{
			return true;
		}
	}
	return false;
}

bool CColliderLine2D::CollisionLine2DtoLine2D(std::shared_ptr<CColliderLine2D> collider)
{
	int ccw1 = CollisionCheck::CCW(mPoint_0, mPoint_1, collider->GetPoint_0());
	int ccw2 = CollisionCheck::CCW(mPoint_0, mPoint_1, collider->GetPoint_1());
	int ccw3 = CollisionCheck::CCW(collider->GetPoint_0(), collider->GetPoint_1(), mPoint_0);
	int ccw4 = CollisionCheck::CCW(collider->GetPoint_0(), collider->GetPoint_1(), mPoint_1);

	if ((ccw1 * ccw2 < 0) && (ccw3 * ccw4 < 0))
		return true;

	return false;
}

void CColliderLine2D::SetPoint_0(float x, float y)
{
	mPoint_0.x = x;
	mPoint_0.y = y;
}

void CColliderLine2D::SetPoint_1(float x, float y)
{
	mPoint_1.x = x;
	mPoint_1.y = y;
}

FVector2D CColliderLine2D::GetPoint_0()
{
	return mPoint_0;
}

FVector2D CColliderLine2D::GetPoint_1()
{
	return mPoint_1;
}

void CColliderLine2D::UpdateTransform()
{
}