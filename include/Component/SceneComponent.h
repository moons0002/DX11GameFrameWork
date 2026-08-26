#pragma once

#include "../GameInfo.h"
#include "../Share/object.h"

class CScene;

class CSceneComponent : public CObject, public std::enable_shared_from_this<CSceneComponent>
{
	friend class CSceneObject;

public:
	CSceneComponent();
	virtual ~CSceneComponent();

protected:
	std::weak_ptr<CSceneObject> mParentObj;
	std::weak_ptr<CScene> mScene;
	std::string mName;

public:
	const char* GetName() const
	{
		return mName.c_str();
	}
	std::weak_ptr<CSceneObject> GetParentObj()
	{
		return mParentObj;
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

public:
	virtual bool Init();

	virtual void PreUpdate(float Deltatime);
	virtual void Update(float Deltatime);
	virtual void PostUpdate(float Deltatime);

	virtual void Collision(float Deltatime);

	virtual void PreRender(float DeltaTime);
	virtual void Render();
	virtual void PostRender();

	virtual CSceneComponent* Clone();
};