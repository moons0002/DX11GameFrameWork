#pragma once

#include "../../GameInfo.h"

class CColliderBase;

class CQuadTreeNode : public std::enable_shared_from_this<CQuadTreeNode>
{
public:
	CQuadTreeNode();
	~CQuadTreeNode();

private:
	std::weak_ptr<CQuadTreeNode> mParent;
	std::shared_ptr<CQuadTreeNode> mChild[4];
	
	FVector3D mCenter = {0.f, 0.f, 0.f};
	FVector3D mSize;

	int mDepth = 0;

	std::vector<std::weak_ptr<CColliderBase>> mColliderList;

public:
	void SetParent(std::shared_ptr<CQuadTreeNode> parent)
	{
		mParent = parent;
	}
	void SetSize(float x, float y, float z)
	{
		mSize = FVector3D(x, y, z);
	}

	void AddCollider(std::shared_ptr<CColliderBase> collider);
	void CreateChild();
	void Collision(std::shared_ptr<CColliderBase> collider, float DeltaTime);

	void DeleteExpiredCollider();

private:
	bool IsInCollider(std::shared_ptr<CColliderBase> collider);
};

