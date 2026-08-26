#pragma once

#include "../../GameInfo.h"
#include "QuadTreeNode.h"

class CScene;

class CQuadTree
{
public:
	CQuadTree();
	~CQuadTree();

private:
	std::weak_ptr<CScene> mScene;

	std::vector<std::weak_ptr<CColliderBase>> mColliderList;

	std::shared_ptr<CQuadTreeNode> mRoot;

public:
	void SetScene(std::shared_ptr<CScene> scene)
	{
		mScene = scene;
	}
	
	void AddCollider(std::shared_ptr<CColliderBase> collider);

	bool Init();

	void Collision(float DeltaTime);

	void PostRender();

	void CreateNewQuadTree();
};

