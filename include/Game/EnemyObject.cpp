#include "EnemyObject.h"

#include "../Component/TransformComponent.h"
#include "../Component/AnimationComponent.h"

#include "../Component/ColliderBase.h"

bool CEnemyObject::Init()
{
	mObjectType = ObjectType::Enemy;
	return true;
}

void CEnemyObject::Update(float DeltaTime)
{
	Time += DeltaTime;
	EnemyMoving();
}

void CEnemyObject::Collision(float DeltaTime)
{
	CSceneObject::Collision(DeltaTime);
	auto Object = std::dynamic_pointer_cast<CColliderBase>(FindComponent("Collider").lock())->GetCollisionObjList().back().lock()->GetParentObj().lock();
	if (Object->GetObjectType() == ObjectType::KirbyProjectile)
	{
		AddHp(-10);
	}
}

void CEnemyObject::EnemyMoving()
{
}

void CEnemyObject::AddHp(float Hp)
{
	mHP += Hp;
	if (Hp <= 0)
	{
		Destroy();
	}
}