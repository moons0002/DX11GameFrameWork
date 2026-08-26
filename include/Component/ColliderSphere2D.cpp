#include "ColliderSphere2D.h"

#include "../Object/SceneObject.h"

#include "ColliderAABB2D.h"
#include "ColliderOBB2D.h"
#include "ColliderLine2D.h"

CColliderSphere2D::CColliderSphere2D()
{
}

CColliderSphere2D::~CColliderSphere2D()
{
}

bool CColliderSphere2D::Init()
{
	if (!CColliderBase::Init())
		return false;

	mColliderType = EColliderType::Collider2D;
	mColliderShape = EColliderShape::Sphere2D;

	return true;
}

bool CColliderSphere2D::CheckCollision(std::shared_ptr<CColliderBase> collider, float DeltaTime)
{
	if (collider->GetColliderType() == EColliderType::Collider3D) return false;
	
	switch(collider->GetColliderShape())
	{
	case EColliderShape::Sphere2D:
		if (CollisionSphere2DtoSphere2D(std::dynamic_pointer_cast<CColliderSphere2D>(collider)))
		{
			return true;
		}
	case EColliderShape::AABB2D:
		if (CollisionSphere2DtoAABB2D(std::dynamic_pointer_cast<CColliderAABB2D>(collider)))
		{
			return true;
		}
		break;
	case EColliderShape::OBB2D:
		if (CollisionSphere2DtoOBB2D(std::dynamic_pointer_cast<CColliderOBB2D>(collider)))
		{
			return true;
		}
		break;
	case EColliderShape::Line2D:
		if (CollisionSphere2DtoLine2D(std::dynamic_pointer_cast<CColliderLine2D>(collider)))
		{
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

bool CColliderSphere2D::CollisionSphere2DtoSphere2D(std::shared_ptr<CColliderSphere2D> collider)
{
	// 충돌 확인
	if ((mCenter.Distance(collider->GetCenter())) < (mRadius + collider->GetRadius()))
	{
		return true;
	}
	return false;
}

bool CColliderSphere2D::CollisionSphere2DtoAABB2D(std::shared_ptr<CColliderAABB2D> collider)
{
	float closest_x, closest_y;
	if (mCenter.x < collider->GetMin().x) closest_x = collider->GetMin().x;
	else if (collider->GetMax().x < mCenter.x) closest_x = collider->GetMax().x;
	else closest_x = mCenter.x;

	if (mCenter.y < collider->GetMin().y) closest_y = collider->GetMin().y;
	else if (collider->GetMax().y < mCenter.y) closest_y = collider->GetMax().y;
	else closest_y = mCenter.y;

	float len_x = (closest_x - mCenter.x);
	float len_y = (closest_y - mCenter.y);

	if (sqrt(len_x*len_x + len_y*len_y) < mRadius)
	{
		return true;
	}

	return false;
}

bool CColliderSphere2D::CollisionSphere2DtoOBB2D(std::shared_ptr<CColliderOBB2D> collider)
{
	FVector3D LocalCenter = mCenter - collider->GetCenter();

	FVector3D Rot = collider->GetRot();

	FVector3D rRot = {Rot.x, Rot.y, -Rot.z};

	LocalCenter.Rotation(rRot);
	FVector3D Max = collider->GetMax() - collider->GetCenter();
	FVector3D Min = collider->GetMin() - collider->GetCenter();
	
	float closest_x, closest_y;
	if (LocalCenter.x < Min.x) closest_x = Min.x;
	else if (Max.x < LocalCenter.x) closest_x = Max.x;
	else closest_x = LocalCenter.x;

	if (LocalCenter.y < Min.y) closest_y = Min.y;
	else if (Max.y < LocalCenter.y) closest_y = Max.y;
	else closest_y = LocalCenter.y;

	float len_x = (closest_x - LocalCenter.x);
	float len_y = (closest_y - LocalCenter.y);

	if (sqrt(len_x*len_x + len_y*len_y) < mRadius)
	{
		return true;
	}

	return false;
}

bool CColliderSphere2D::CollisionSphere2DtoLine2D(std::shared_ptr<CColliderLine2D> collider)
{
	FVector2D mPoint_0 = collider->GetPoint_0();
	FVector2D mPoint_1 = collider->GetPoint_1();

	FVector2D Center = FVector2D(mCenter.x, mCenter.y);

	FVector2D v = mPoint_1 - mPoint_0;
	FVector2D w = Center - mPoint_0;

	float t = v.Dot(w) / v.Dot(v);

	if (t < 0) t = 0;
	else if (t > 1) t = 1;

	FVector2D p = mPoint_0 + (mPoint_1 - mPoint_0) * t;

	if (p.Distance(Center) > mRadius)
		return false;

	return true;
}

void CColliderSphere2D::UpdateTransform()
{
	CColliderBase::UpdateTransform();

	// 수정
	mRadius = mSize.x / 2.f;
}
