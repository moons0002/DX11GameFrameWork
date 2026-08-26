#include "ColliderOBB2D.h"

#include "../Object/SceneObject.h"
#include "TransformComponent.h"

#include "ColliderAABB2D.h"
#include "ColliderSphere2D.h"
#include "ColliderLine2D.h"

CColliderOBB2D::CColliderOBB2D()
{
}

CColliderOBB2D::~CColliderOBB2D()
{
}

bool CColliderOBB2D::Init()
{
	if (!CColliderBase::Init())
		return false;

	mColliderType = EColliderType::Collider2D;
	mColliderShape = EColliderShape::OBB2D;

	return true;
}

bool CColliderOBB2D::CheckCollision(std::shared_ptr<CColliderBase> collider, float DeltaTime)
{
	if (collider->GetColliderType() == EColliderType::Collider3D) return false;
	
	switch(collider->GetColliderShape())
	{
	case EColliderShape::OBB2D:
		if (CollisionOBB2DtoOBB2D(std::dynamic_pointer_cast<CColliderOBB2D>(collider)))
		{
			return true;
		}
		break;
	case EColliderShape::Sphere2D:
		if (CollisionOBB2DtoSphere2D(std::dynamic_pointer_cast<CColliderSphere2D>(collider)))
		{
			return true;
		}
		break;
	case EColliderShape::AABB2D:
		if (CollisionOBB2DtoAABB2D(std::dynamic_pointer_cast<CColliderAABB2D>(collider)))
		{
			return true;
		}
		break;
	case EColliderShape::Line2D:
		if (CollisionOBB2DtoLine2D(std::dynamic_pointer_cast<CColliderLine2D>(collider)))
		{
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

bool CColliderOBB2D::CollisionOBB2DtoOBB2D(std::shared_ptr<CColliderOBB2D> collider)
{
	FVector2D axis[4] = 
	{
		mOBB.axis0,
		mOBB.axis1,
		collider->mOBB.axis0,
		collider->mOBB.axis1
	};

	for (int i = 0; i < 4; i++)
	{
		FVector3D centerVector = mCenter - collider->GetCenter();
		FVector2D centerVector2D = FVector2D(centerVector.x, centerVector.y);
		float length = abs(centerVector2D.Dot(axis[i]));

		// 둘중에 큰거 선택
		float len0 = abs(mOBB.v0.Dot(axis[i]));
		float len1 = abs(mOBB.v1.Dot(axis[i]));

		float max0 = len0 > len1 ? len0 : len1;

		// 둘중에 큰거 선택
		len0 = abs((collider->mOBB.v0).Dot(axis[i]));
		len1 = abs((collider->mOBB.v1).Dot(axis[i]));
		
		float max1 = len0 > len1 ? len0 : len1;

		// 위에 두개를 더한거 < length 라면 안 겹침...
		if ((max0 + max1) < length)
		{
			return false;
		}
	}
	return true;
}

bool CColliderOBB2D::CollisionOBB2DtoAABB2D(std::shared_ptr<CColliderAABB2D> collider)
{
	FVector2D axis[4] = 
	{
		mOBB.axis0,
		mOBB.axis1,
		{1.f, 0.f},
		{0.f, 1.f}
	};

	for (int i = 0; i < 4; i++)
	{
		FVector3D centerVector = mCenter - collider->GetCenter();
		FVector2D centerVector2D = FVector2D(centerVector.x, centerVector.y);
		float length = abs(centerVector2D.Dot(axis[i]));

		// 둘중에 큰거 선택
		float len0 = abs(mOBB.v0.Dot(axis[i]));
		float len1 = abs(mOBB.v1.Dot(axis[i]));

		float max0 = len0 > len1 ? len0 : len1;

		// 둘중에 큰거 선택
		len0 = abs((FVector2D(collider->GetMax().x, collider->GetMax().y)).Dot(axis[i]));
		len1 = abs((FVector2D(collider->GetMax().x, -(collider->GetMax().y))).Dot(axis[i]));
		
		float max1 = len0 > len1 ? len0 : len1;

		// 위에 두개를 더한거 < length 라면 안 겹침...
		if ((max0 + max1) < length)
		{
			return false;
		}
	}
	return true;
}

bool CColliderOBB2D::CollisionOBB2DtoSphere2D(std::shared_ptr<CColliderSphere2D> collider)
{
	FVector3D LocalCenter = collider->GetCenter() - mCenter;

	FVector3D rRot = {mRot.x, mRot.y, -mRot.z};

	LocalCenter.Rotation(rRot);

	FVector3D LocalMax = mMax - mCenter;
	FVector3D LocalMin = mMin - mCenter;
	
	float closest_x, closest_y;
	if (LocalCenter.x < LocalMin.x) closest_x = LocalMin.x;
	else if (LocalMax.x < LocalCenter.x) closest_x = LocalMax.x;
	else closest_x = LocalCenter.x;

	if (LocalCenter.y < LocalMin.y) closest_y = LocalMin.y;
	else if (LocalMax.y < LocalCenter.y) closest_y = LocalMax.y;
	else closest_y = LocalCenter.y;

	float len_x = (closest_x - LocalCenter.x);
	float len_y = (closest_y - LocalCenter.y);

	if (sqrt(len_x*len_x + len_y*len_y) < collider->GetRadius())
	{
		return true;
	}

	return false;
}

bool CColliderOBB2D::CollisionOBB2DtoLine2D(std::shared_ptr<CColliderLine2D> collider)
{
	FVector2D mPoint_0 = collider->GetPoint_0();
	FVector2D mPoint_1 = collider->GetPoint_1();

	FVector3D p0 = {mPoint_0.x, mPoint_0.y, 0};
	p0.Rotation(-mRot);
 	FVector3D p1 = {mPoint_1.x, mPoint_1.y, 0};
	p1.Rotation(-mRot);

	FVector2D Dir = {p0.x - p1.x, p0.y - p1.y};

	float a = (Dir.y) / (Dir.x);
	float b = a * p0.x + p0.y;

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

void CColliderOBB2D::UpdateTransform()
{
	CColliderBase::UpdateTransform();

	FVector3D v0 = (mMax - mCenter);
	FVector3D v1 = v0 - FVector3D(0.f, 2*v0.y, 0.f);

	FVector3D axis0 = {1.f, 0.f, 0.f};
	FVector3D axis1 = {0.f, 1.f, 0.f};

	mRot =  std::dynamic_pointer_cast<CTransformComponent>(mParentObj.lock()->FindComponent("Transform").lock())->GetWorldRotation();

	v0 = v0.Rotation(mRot);
	v1 = v1.Rotation(mRot);

	axis0 = axis0.Rotation(mRot);
	axis1 = axis1.Rotation(mRot);

	mOBB.v0 = {v0.x, v0.y};
	mOBB.v1 = {v1.x, v1.y};

	mOBB.axis0 = {axis0.x , axis0.y};
	mOBB.axis1 = {axis1.x , axis1.y};
}
