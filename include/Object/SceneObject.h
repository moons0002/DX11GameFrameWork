#pragma once
#include "../Share/object.h"
#include "../GameInfo.h"
#include "../Component/SceneComponent.h"

enum class ObjectType
{
	Kirby,
	Enemy,
	KirbyProjectile,
	EnemyProjectile,
	UI,
	BackGround,
	Map,
	Door,
	Ground
};

enum class ObjectViewPort
{
	Full,
	Top,
	Bottom
};

class CScene;

class CSceneObject : public CObject, public std::enable_shared_from_this<CSceneObject>
{
	friend class CScene;
public:
	CSceneObject();
	virtual ~CSceneObject();

public:
	std::weak_ptr<CSceneObject> mParentObj;
	std::weak_ptr<CScene> mScene;
	std::string mName;

	ObjectType mObjectType;

	FVector3D mSize;

	ObjectViewPort mViewPort = ObjectViewPort::Top;

public:
	std::list<std::shared_ptr<CSceneObject>> mChildObjList = {};
	std::list<std::shared_ptr<CSceneComponent>> mComponentList = {};
	
public:
	std::weak_ptr<CScene> GetScene() const
	{
		return mScene;
	}
	const char* GetName() const
	{
		return mName.c_str();
	}

	void SetParentObj(std::weak_ptr<CSceneObject> Obj)
	{

		mParentObj = Obj;
	}
	void SetScene(std::weak_ptr<CScene> Scene)
	{
		mScene = Scene;
	}
	void SetName(const std::string& Name)
	{
		mName = Name;
	}
	void SetViewPort(ObjectViewPort ViewPort)
	{
		mViewPort = ViewPort;
	}

	ObjectType GetObjectType()
	{
		return mObjectType;
	}
	ObjectViewPort GetViewPort()
	{
		return mViewPort;
	}

public:
	template <typename T>
	bool CreateChildObject(const std::string& Name)
	{
		std::shared_ptr<CSceneObject> Obj = FindObject(Name).lock();

		if (Obj)
		{
			return true;
		}

		Obj = std::make_shared<T>();
		Obj->SetScene(mScene);
		Obj->SetParentObj(shared_from_this());
		Obj->SetName(Name);

		if (!Obj->Init())
		{
			return false;
		}

		mChildObjList.push_back(Obj);

		return true;
	}

	template <typename T>
	bool CreateComponent(const std::string& Name)
	{
		std::shared_ptr<CSceneComponent> Comp = FindComponent(Name).lock();

		if (Comp)
		{
			return true;
		}

		Comp = std::make_shared<T>();
		Comp->SetScene(mScene);
		Comp->SetParentObj(shared_from_this());
		Comp->SetName(Name);

		if (!Comp->Init())
		{
			return false;
		}

		mComponentList.push_back(Comp);
		return true;
	}

	virtual std::weak_ptr<CSceneObject> FindObject(const std::string& Name);
	virtual std::weak_ptr<CSceneComponent> FindComponent(const std::string& Name);

public:
	virtual bool Init();

	virtual void PreUpdate(float Deltatime);
	virtual void Update(float Deltatime);
	virtual void PostUpdate(float Deltatime);

	virtual void Collision(float Deltatime);

	virtual void PreRender(float DeltaTime);
	virtual void Render();
	virtual void PostRender();

	virtual CSceneObject* Clone();
};