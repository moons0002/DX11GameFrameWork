#include "InhalableEnemyObject.h"

#include "../Scene/Scene.h"
#include "../Component/TransformComponent.h"
#include "InhaleComponent.h"
#include "KirbyStateComponent.h"
#include "../Component/MovementConstraintComponent.h"

EInhalableEnemyType InhalableEnemyObject::GetInhalableEnemyType()
{
	return mInhalableEnemyType;
}

bool InhalableEnemyObject::Init()
{
	mObjectType = ObjectType::Enemy;
	return false;
}

void InhalableEnemyObject::Update(float DeltaTime)
{
	CEnemyObject::Update(DeltaTime);

	if (InhalingStart == true)
	{
		PrevTime = Time;
		InhalingStart = false;
	}
	if (IsInhaled == true)
	{
		std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock())->SetVelocity(0.f, 0.f);
		if ((Time - PrevTime) > 0.7f)
		{
			std::weak_ptr<CSceneObject> Kirby = mScene.lock()->FindObject("Kirby");
			KirbyTransform = std::dynamic_pointer_cast<CTransformComponent>(Kirby.lock()->FindComponent("Transform").lock());
			MyTransform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());

			FVector3D Direction = (KirbyTransform.lock()->GetWorldPosition() - MyTransform.lock()->GetWorldPosition());
			Direction.Normalize();

			MyTransform.lock()->SetVelocity(Direction.x * InhaleSpeed, Direction.y * InhaleSpeed);

			std::dynamic_pointer_cast<KirbyStateComponent>(Kirby.lock()->FindComponent("KirbyState").lock())->StopAndInhale();
			std::dynamic_pointer_cast<MovementConstraintComponent>(FindComponent("MovementConstraint").lock())->SetEnable(false);
			FindComponent("Collider").lock()->SetEnable(false);

			IsInhalingEnd = true;
			IsInhaled = false;
		}
	}
	else if (IsInhalingEnd == true)
	{
		// 커비와 가까이 있는지 확인
		// 가까이 있으면 사라짐
		if ((KirbyTransform.lock()->GetWorldPosition()).Distance(MyTransform.lock()->GetWorldPosition()) < 20.f)
		{
			IsInhalingEnd = false;
			std::dynamic_pointer_cast<CInhaleComponent>(mScene.lock()->FindObject("Kirby").lock()->FindComponent("Inhale").lock())->CompleteInhale(mInhalableEnemyType);
			Destroy();
		}
	}
}

void InhalableEnemyObject::StartInhaled()
{
	InhalingStart = true;
	IsInhaled = true;
}

void InhalableEnemyObject::StopInhaled()
{
	IsInhaled = false;
}