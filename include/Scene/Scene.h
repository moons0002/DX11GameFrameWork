#pragma once

#include "../GameInfo.h"
#include "../Share/Object.h"
#include "../Object/SceneObject.h"

#include "Input/Input.h"
#include "Camera/Camera.h"
#include "Camera/UICamera.h"
#include "Collision/QuadTree.h"
#include "../Component/ColliderBase.h"

class CScene : public CObject, public std::enable_shared_from_this<CScene>
{
	friend class CSceneManager;
public:
	CScene();
	virtual ~CScene();

protected:
	std::list<std::shared_ptr<CSceneObject>> mObjList;

	std::shared_ptr<CInput> mInput;
	std::shared_ptr<CCamera> mCamera;
	std::shared_ptr<UICamera> mUICamera;
	std::shared_ptr<CQuadTree> mQuadTree;

	FVector2D mSize = {0.f, 0.f};

public:
	std::shared_ptr<CInput> GetInput() const
	{
		return mInput;
	}
	std::shared_ptr<CCamera> GetCamera() const
	{
		return mCamera;
	}
	std::shared_ptr<UICamera> GetUICamera() const
	{
		return mUICamera;
	}
	std::shared_ptr<CQuadTree> GetQuadTree() const
	{
		return mQuadTree;
	}

	FVector2D GetSize()
	{
		return mSize;
	}

	void AddCollider(std::shared_ptr<CColliderBase> collider);

	void SetCameraTarget(std::shared_ptr<CSceneObject> Obj);
	void SetSize(FVector2D Size);

	virtual void StartChangeStage(std::string StageName, FVector2D Position);

public:
	virtual bool Init();

	virtual void Input(float DeltaTime);

	virtual void PreUpdate(float Deltatime);
	virtual void Update(float Deltatime);
	virtual void PostUpdate(float Deltatime);

	virtual void Collision(float Deltatime);

	virtual void PreRender(float DeltaTime);
	virtual void Render();
	virtual void PostRender();

public:
	template <typename T>
	bool CreateObject(const std::string& Name)
	{
		std::shared_ptr<CSceneObject> Obj = FindObject(Name).lock();

		if (Obj)
		{
			return true;
		}
		
		Obj = std::make_shared<T>();
		Obj->SetScene(shared_from_this());
		Obj->SetName(Name);

		if (!Obj->Init())
		{
			return false;
		}

		mObjList.push_back(Obj);

		return true;
	}

	std::weak_ptr<CSceneObject> FindObject(const std::string& Name);
};