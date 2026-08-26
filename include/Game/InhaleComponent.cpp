#include "InhaleComponent.h"

#include "StageScene.h"
#include "InhalableEnemyObject.h"

#include "../Component/TransformComponent.h"
#include "KirbyStateComponent.h"

void CInhaleComponent::StartInhale(bool IsLookingRight)
{
	auto EnemyList = std::dynamic_pointer_cast<StageScene>(mScene.lock())->GetEnemyList();

	auto iter = EnemyList.begin();
	auto iterEnd = EnemyList.end();

	FVector3D Center = std::dynamic_pointer_cast<CTransformComponent>(mParentObj.lock()->FindComponent("Transform").lock())->GetWorldPosition();

	std::weak_ptr<CEnemyObject> NearestEnemy;

	float MinDistance = mSmallSize.x;

	for (; iter != iterEnd; ++iter)
	{
		if (!(iter->lock()->GetEnemyType() == EnemyType::Inhalable)) continue;

		FVector3D WorldPos = std::dynamic_pointer_cast<CTransformComponent>(iter->lock()->FindComponent("Transform").lock())->GetWorldPosition();

		if (Center.Distance(WorldPos) >= MinDistance) continue;
					
		if (Center.y - mSmallSize.y <= WorldPos.y && Center.y + WorldPos.y <= mSmallSize.y)
		{
			if (IsLookingRight)
			{
				// 오른쪽을 바라볼때
				if (Center.x < WorldPos.x && WorldPos.x < (Center.x + mSmallSize.x))
				{
					NearestEnemy = *iter;
					MinDistance = Center.Distance(WorldPos);
				}
			}
			else if (!IsLookingRight)
			{
				// 왼쪽을 바라볼때
				if (Center.x > WorldPos.x && WorldPos.x > (Center.x - mSmallSize.x))
				{
					NearestEnemy = *iter;
					MinDistance = Center.Distance(WorldPos);
				}
			}
		}
	}

	if (NearestEnemy.expired()) return;
	mInhaleEnemy = NearestEnemy;
	std::dynamic_pointer_cast<InhalableEnemyObject>(mInhaleEnemy.lock())->StartInhaled();
}

void CInhaleComponent::StopInhale()
{
	if (mInhaleEnemy.expired()) return;
	std::dynamic_pointer_cast<InhalableEnemyObject>(mInhaleEnemy.lock())->StopInhaled();
	mInhaleEnemy.reset();
}

void CInhaleComponent::CompleteInhale(EInhalableEnemyType EnemyType)
{
	std::dynamic_pointer_cast<KirbyStateComponent>(mParentObj.lock()->FindComponent("KirbyState").lock())->HoldingIn(EnemyType);
}
