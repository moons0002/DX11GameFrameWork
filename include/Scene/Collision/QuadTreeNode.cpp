#include "QuadTreeNode.h"

#include "../../Component/ColliderBase.h"
#include "../../ProfileManager.h"
#include "../../Object/SceneObject.h"

CQuadTreeNode::CQuadTreeNode()
{
}

CQuadTreeNode::~CQuadTreeNode()
{
}

void CQuadTreeNode::AddCollider(std::shared_ptr<CColliderBase> collider)
{
	if (!IsInCollider(collider))
	{
		return;
	}
	if (!mChild[0])
	{
		mColliderList.emplace_back(collider);
		
		// 자식 노드로 분할
		if (mColliderList.size() >= 5 && mDepth < 4)
		{
			CreateChild();

			size_t Size = mColliderList.size();
			for (size_t i = 0; i < Size; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (mChild[j]->IsInCollider(mColliderList[i].lock()))
					{
						mChild[j]->AddCollider(mColliderList[i].lock());
					}
				}
			}
			
			mColliderList.clear();
		}
	}
	else
	{
		mChild[0]->AddCollider(collider);
		mChild[1]->AddCollider(collider);
		mChild[2]->AddCollider(collider);
		mChild[3]->AddCollider(collider);
	}
}

void CQuadTreeNode::CreateChild()
{
	for (int i = 0; i < 4; ++i)
	{
		mChild[i] = std::make_shared<CQuadTreeNode>();

		mChild[i]->mSize = mSize * 0.5f;

		if (i % 2 == 0)
		{
			mChild[i]->mCenter.x = mCenter.x + mSize.x * 0.25f;
		}
		else
		{
			mChild[i]->mCenter.x = mCenter.x - mSize.x * 0.25f;
		}
		if (i <= 1)
		{
			mChild[i]->mCenter.y = mCenter.y + mSize.y * 0.25f;
		}
		else
		{
			mChild[i]->mCenter.y = mCenter.y - mSize.y * 0.25f;
		}

		mChild[i]->mDepth = mDepth + 1;
		mChild[i]->mParent = shared_from_this();
	}
}

bool CQuadTreeNode::IsInCollider(std::shared_ptr<CColliderBase> collider)
{
	FVector3D NodeMin, NodeMax;
	NodeMin = mCenter - mSize * 0.5f;
	NodeMax = mCenter + mSize * 0.5f;
	if ((NodeMin.x < collider->GetMax().x) && (collider->GetMin().x < NodeMax.x) &&
		(NodeMin.y < collider->GetMax().y) && (collider->GetMin().y < NodeMax.y))
	{
		return true;
	}
	return false;
}

void CQuadTreeNode::Collision(std::shared_ptr<CColliderBase> collider, float DeltaTime)
{
	// 여기서 충돌하면... 그 collider의 충돌함수 실행시켜주기
	if (!IsInCollider(collider))
	{
		return;
	}
	if (!mChild[0])
	{
		CProfileManager& ProfileManager = CProfileManager::GetInstance();
		// 자식이 없다면 모든 리스트를 검사해서 충돌하는지 확인
		for (auto o : mColliderList)
		{
			// 본인이라면 넘김
			if (collider == o.lock())
			{
				continue;
			}
			if (o.expired())
			{
				continue;
			}

			if (!(collider->GetParentObj().lock()->IsActive() && collider->GetParentObj().lock()->IsEnable()))
				break;

			// 프로파일로 충돌체크..
			std::shared_ptr<FCollisionProfile> profile = ProfileManager.FindProfile(collider->GetChannel());
			if ((profile->Enable) && (profile->Interaction[ProfileManager.FindProfile(o.lock()->GetChannel())->Channel] == ECollisionInteraction::Collision))
			{
				if (o.lock()->IsEnable() && o.lock()->IsActive())
				{
					if (collider->CheckCollision(o.lock(), DeltaTime))
					{
						collider->GetCollisionObjList().push_back(o);
						collider->GetParentObj().lock()->Collision(DeltaTime);
					}
				}
			}
		}
	}
	else
	{
		// 자식이 있다면 자식 리스트에게 충돌을 확인
		mChild[0]->Collision(collider, DeltaTime);
		mChild[1]->Collision(collider, DeltaTime);
		mChild[2]->Collision(collider, DeltaTime);
		mChild[3]->Collision(collider, DeltaTime);
	}
}

void CQuadTreeNode::DeleteExpiredCollider()
{
	// 자식을 다 돌면서 expired면 erase
	if (!mChild[0])
	{
		auto iter = mColliderList.begin();
		auto iterEnd = mColliderList.end();

		for (; iter != iterEnd;)
		{
			if (iter->expired())
			{
				iter = mColliderList.erase(iter);
				iterEnd = mColliderList.end();
				continue;
			}
			++iter;
		}
	}
	else
	{
		mChild[0]->DeleteExpiredCollider();
		mChild[1]->DeleteExpiredCollider();
		mChild[2]->DeleteExpiredCollider();
		mChild[3]->DeleteExpiredCollider();
	}
}
