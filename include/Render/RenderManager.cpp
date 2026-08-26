#include "RenderManager.h"

#include "RenderStateManager.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/AnimationComponent.h"
#include "../Object/SceneObject.h"
#include "../Device.h"
#include "../Asset/AssetManager.h"

CRenderManager::CRenderManager()
{
	
}

CRenderManager::~CRenderManager()
{
}

void CRenderManager::PushBackRenderList(std::weak_ptr<CSceneObject> Comp)
{
	mRenderList.push_back(Comp);
}

void CRenderManager::PushBackUIRenderList(std::weak_ptr<CSceneObject> Comp)
{
	mUIRenderList.push_back(Comp);
}

bool CRenderManager::Init()
{
	mStateManager = std::make_shared<CRenderStateManager>();

	if (!mStateManager->Init())
	{
		return false;
	}

	return true;
}

void CRenderManager::Render()
{
	CAssetManager::GetInstance().GetEffectManager()->Render();

	std::list<std::weak_ptr<CSceneObject>>::iterator iter = mRenderList.begin();
	std::list<std::weak_ptr<CSceneObject>>::iterator iterEnd = mRenderList.end();

	for (; iter != iterEnd;)
	{
		if (iter->expired())
		{
			iter = mRenderList.erase(iter);
			iterEnd = mRenderList.end();
			continue;
		}

		switch (iter->lock()->GetViewPort())
		{
		case ObjectViewPort::Full:
			CDevice::GetInstance().UseFullScreen();
			break;
		case ObjectViewPort::Top:
			CDevice::GetInstance().UseTopScreen();
			break;
		case ObjectViewPort::Bottom:
			CDevice::GetInstance().UseBottomScreen();
			break;
		default:
			break;
		}

		iter->lock()->Render();
		++iter;
	}

	mRenderList.sort([](std::weak_ptr<CSceneObject> a, std::weak_ptr<CSceneObject> b){
	return std::dynamic_pointer_cast<CAnimationComponent>(a.lock()->FindComponent("Animation").lock())->GetSortingOrder() >
		std::dynamic_pointer_cast<CAnimationComponent>(b.lock()->FindComponent("Animation").lock())->GetSortingOrder();
	});
}

void CRenderManager::ClearRenderList()
{
	mRenderList.clear();
}
