#include "QuadTree.h"

#include "../../Device.h"
#include "../Scene.h"

CQuadTree::CQuadTree()
{
}

CQuadTree::~CQuadTree()
{
}

bool CQuadTree::Init()
{
	mRoot = std::make_shared<CQuadTreeNode>();
	
	const FResolution& RS = CDevice::GetInstance().GetResolution();

	mRoot->SetSize(mScene.lock()->GetSize().x * 1.5f, mScene.lock()->GetSize().y * 1.5f, 0.f);

	return true;
}

void CQuadTree::AddCollider(std::shared_ptr<CColliderBase> collider)
{
	mColliderList.emplace_back(collider);
	mRoot->AddCollider(collider);
}

void CQuadTree::Collision(float DeltaTIme)
{
	for (auto o : mColliderList)
	{
		o.lock()->UpdateTransform();
	}

	CreateNewQuadTree();

	std::vector<std::weak_ptr<CColliderBase>>::iterator iterObj = mColliderList.begin();
	std::vector<std::weak_ptr<CColliderBase>>::iterator iterObjEnd = mColliderList.end();

	for (; iterObj != iterObjEnd;)
	{
		if (iterObj->expired() || !((iterObj->lock()->IsActive()) && (iterObj->lock()->IsEnable())))
		{
			++iterObj;
			continue;
		}

		mRoot->Collision(iterObj->lock(), DeltaTIme);
		++iterObj;
	}
}

void CQuadTree::PostRender()
{
	std::vector<std::weak_ptr<CColliderBase>>::iterator iterObj = mColliderList.begin();
	std::vector<std::weak_ptr<CColliderBase>>::iterator iterObjEnd = mColliderList.end();

	for (; iterObj != iterObjEnd;)
	{
		if (iterObj->expired() || (!(iterObj->lock()->IsActive())))
		{
			iterObj = mColliderList.erase(iterObj);
			iterObjEnd = mColliderList.end();
			continue;
		}
		++iterObj;
	}
	mRoot->DeleteExpiredCollider();
}

void CQuadTree::CreateNewQuadTree()
{
	Init();

	std::vector<std::weak_ptr<CColliderBase>>::iterator iter = mColliderList.begin();
	std::vector<std::weak_ptr<CColliderBase>>::iterator iterEnd = mColliderList.end();

	for (;iter != iterEnd; ++iter)
	{
		mRoot->AddCollider((*iter).lock());
	}
}
