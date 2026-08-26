#include "Scene.h"

#include "../Render/RenderManager.h"
#include "../Asset/AssetManager.h"

#include "../Component/TransformComponent.h"

CScene::CScene()
{

}

CScene::~CScene()
{
}

void CScene::AddCollider(std::shared_ptr<CColliderBase> collider)
{
	mQuadTree->AddCollider(collider);
}

void CScene::SetCameraTarget(std::shared_ptr<CSceneObject> Obj)
{
	mCamera->SetTarget(&(std::dynamic_pointer_cast<CTransformComponent>(Obj->FindComponent("Transform").lock())->GetWorldPosition()));
}

void CScene::SetSize(FVector2D Size)
{
	mSize = Size;
}

void CScene::StartChangeStage(std::string StageName, FVector2D Position)
{
}

bool CScene::Init()
{
	mInput = std::make_shared<CInput>();
	mCamera = std::make_shared<CCamera>();
	mUICamera = std::make_shared<UICamera>();
	mQuadTree = std::make_shared<CQuadTree>();

	mCamera->SetParentScene(shared_from_this());
	mQuadTree->SetScene(shared_from_this());

	if (!mInput->Init())
		return false;
	if (!mCamera->Init())
		return false;
	if (!mQuadTree->Init())
		return false;
	if (!mUICamera->Init())
		return false;

	return true;
}

void CScene::Input(float DeltaTime)
{
	mInput->Update(DeltaTime);
}

void CScene::PreUpdate(float Deltatime)
{
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObj = mObjList.begin();
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObjEnd = mObjList.end();

	for (; iterObj != iterObjEnd; ++iterObj)
	{
		if (!((iterObj->get()->IsActive()) && (iterObj->get()->IsEnable())))
		{
			continue;
		}

		iterObj->get()->PreUpdate(Deltatime);
	}

	CAssetManager::GetInstance().PreUpdate(Deltatime);
}

void CScene::Update(float Deltatime)
{
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObj = mObjList.begin();
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObjEnd = mObjList.end();

	for (; iterObj != iterObjEnd; ++iterObj)
	{
		if (!((iterObj->get()->IsActive()) && (iterObj->get()->IsEnable())))
		{
			continue;
		}

		iterObj->get()->Update(Deltatime);
	}
}

void CScene::PostUpdate(float Deltatime)
{
	mCamera->PostUpdate();

	std::list<std::shared_ptr<CSceneObject>>::iterator iterObj = mObjList.begin();
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObjEnd = mObjList.end();

	for (; iterObj != iterObjEnd; ++iterObj)
	{
		if (!((iterObj->get()->IsActive()) && (iterObj->get()->IsEnable())))
		{
			continue;
		}
		
		iterObj->get()->PostUpdate(Deltatime);
	}
}

void CScene::Collision(float Deltatime)
{
	mQuadTree->Collision(Deltatime);
}

void CScene::PreRender(float DeltaTime)
{
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObj = mObjList.begin();
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObjEnd = mObjList.end();

	for (; iterObj != iterObjEnd; ++iterObj)
	{
		if (!((iterObj->get()->IsActive()) && (iterObj->get()->IsEnable())))
		{
			continue;
		}

		iterObj->get()->PreRender(DeltaTime);
	}
}

void CScene::Render()
{
	// RenderManager 사용
	CRenderManager::GetInstance().Render();

	//std::list<std::shared_ptr<CSceneObject>>::iterator iterObj = mObjList.begin();
	//std::list<std::shared_ptr<CSceneObject>>::iterator iterObjEnd = mObjList.end();
	//for (; iterObj != iterObjEnd; ++iterObj)
	//{
	//	if (!((iterObj->get()->IsActive()) && (iterObj->get()->IsEnable())))
	//	{
	//		continue;
	//	}
	//	iterObj->get()->Render();
	//}
}

void CScene::PostRender()
{
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObj = mObjList.begin();
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObjEnd = mObjList.end();

	for (; iterObj != iterObjEnd; ++iterObj)
	{
		if (!((iterObj->get()->IsActive()) && (iterObj->get()->IsEnable())))
		{
			continue;
		}

		iterObj->get()->PostRender();
	}

	/// 삭제

	for (iterObj = mObjList.begin(); iterObj != iterObjEnd;)
	{
		if (!(iterObj->get()->IsActive()))
		{
			iterObj = mObjList.erase(iterObj);
			iterObjEnd = mObjList.end();
			continue;
		}
		++iterObj;
	}

	mQuadTree->PostRender();
}

std::weak_ptr<CSceneObject> CScene::FindObject(const std::string & Name)
{
	for (std::shared_ptr<CSceneObject> obj : mObjList)
	{
		if (obj.get()->GetName() == Name) return obj;
	}
	return std::weak_ptr<CSceneObject>();
}