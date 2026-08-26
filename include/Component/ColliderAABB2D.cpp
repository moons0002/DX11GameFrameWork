#include "ColliderAABB2D.h"

#include "../Object/SceneObject.h"

#include "ColliderSphere2D.h"
#include "ColliderOBB2D.h"
#include "ColliderLine2D.h"

CColliderAABB2D::CColliderAABB2D()
{
}

CColliderAABB2D::~CColliderAABB2D()
{
}

bool CColliderAABB2D::Init()
{
	if (!CColliderBase::Init())
		return false;

	mColliderType = EColliderType::Collider2D;
	mColliderShape = EColliderShape::AABB2D;

	return true;
}

bool CColliderAABB2D::CheckCollision(std::shared_ptr<CColliderBase> collider, float DeltaTime)
{
	if (collider->GetColliderType() == EColliderType::Collider3D) return false;
	
	switch(collider->GetColliderShape())
	{
	case EColliderShape::AABB2D:
		if (CollisionAABB2DtoAABB2D(std::dynamic_pointer_cast<CColliderAABB2D>(collider)))
		{
			return true;
		}
		break;
	case EColliderShape::Sphere2D:
		if (CollisionAABB2DtoSphere2D(std::dynamic_pointer_cast<CColliderSphere2D>(collider)))
		{
			return true;
		}
		break;
	case EColliderShape::OBB2D:
		if (CollisionAABB2DtoOBB2D(std::dynamic_pointer_cast<CColliderOBB2D>(collider)))
		{
			return true;
		}
		break;
	case EColliderShape::Line2D:
		if (CollisionAABB2DtoLine2D(std::dynamic_pointer_cast<CColliderLine2D>(collider)))
		{
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

bool CColliderAABB2D::CollisionAABB2DtoAABB2D(std::shared_ptr<CColliderAABB2D> collider)
{
	// 충돌 확인
	if ((GetMin().x < collider->GetMax().x) && (collider->GetMin().x < GetMax().x) &&
	(GetMin().y < collider->GetMax().y) && (collider->GetMin().y < GetMax().y))
	{
		return true;
	}
	return false;
}

bool CColliderAABB2D::CollisionAABB2DtoSphere2D(std::shared_ptr<CColliderSphere2D> collider)
{
	float closest_x, closest_y;
	if (collider->GetCenter().x < mMin.x) closest_x = mMin.x;
	else if (mMax.x < collider->GetCenter().x) closest_x = mMax.x;
	else closest_x = collider->GetCenter().x;

	if (collider->GetCenter().y < mMin.y) closest_y = mMin.y;
	else if (mMax.y < collider->GetCenter().y) closest_y = mMax.y;
	else closest_y = collider->GetCenter().y;

	float len_x = (closest_x - collider->GetCenter().x);
	float len_y = (closest_y - collider->GetCenter().y);

	if (sqrt(len_x*len_x + len_y*len_y) < collider->GetRadius())
	{
		return true;
	}

	return false;
}

bool CColliderAABB2D::CollisionAABB2DtoOBB2D(std::shared_ptr<CColliderOBB2D> collider)
{
	FVector2D axis[4] = 
	{
		collider->GetOBB().axis0,
		collider->GetOBB().axis1,
		{1.f, 0.f},
		{0.f, 1.f}
	};

	for (int i = 0; i < 4; i++)
	{
		FVector3D centerVector = mCenter - collider->GetCenter();
		FVector2D centerVector2D = FVector2D(centerVector.x, centerVector.y);
		float length = abs(centerVector2D.Dot(axis[i]));

		// 둘중에 큰거 선택
		float len0 = abs(collider->GetOBB().v0.Dot(axis[i]));
		float len1 = abs(collider->GetOBB().v1.Dot(axis[i]));

		float max0 = len0 > len1 ? len0 : len1;

		// 둘중에 큰거 선택
		len0 = abs((FVector2D(mMax.x, mMax.y)).Dot(axis[i]));
		len1 = abs((FVector2D(mMax.x, -mMax.y)).Dot(axis[i]));
		
		float max1 = len0 > len1 ? len0 : len1;

		// 위에 두개를 더한거 < length 라면 안 겹침...
		if ((max0 + max1) < length)
		{
			return false;
		}
	}
	return true;
}

bool CColliderAABB2D::CollisionAABB2DtoLine2D(std::shared_ptr<CColliderLine2D> collider)
{
	FVector2D mPoint_0 = collider->GetPoint_0();
	FVector2D mPoint_1 = collider->GetPoint_1();
	FVector2D Dir = mPoint_0 - mPoint_1;

	float a = (Dir.y) / (Dir.x);
	float b = a * mPoint_0.x + mPoint_0.y;

	FVector2D Max = {mMax.x, mMax.y};
	FVector2D Min = {mMin.x, mMin.y};

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
