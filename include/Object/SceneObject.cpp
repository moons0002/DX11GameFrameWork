#include "SceneObject.h"
#include "../Component/SceneComponent.h"

CSceneObject::CSceneObject()
{
}

CSceneObject::~CSceneObject()
{
}

std::weak_ptr<CSceneObject> CSceneObject::FindObject(const std::string& Name)
{
	for (std::shared_ptr<CSceneObject> obj : mChildObjList)
	{
		if (obj.get()->GetName() == Name) return obj;
	}
	return std::weak_ptr<CSceneObject>();
}

std::weak_ptr<CSceneComponent> CSceneObject::FindComponent(const std::string& Name)
{
	for (std::shared_ptr<CSceneComponent> comp : mComponentList)
	{
		if (comp->GetName() == Name) return comp;
	}
	return std::weak_ptr<CSceneComponent>();
}

bool CSceneObject::Init()
{
	return true;
}

void CSceneObject::PreUpdate(float Deltatime)
{
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObj = mChildObjList.begin();
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObjEnd = mChildObjList.end();

	for (; iterObj != iterObjEnd; iterObj++)
	{
		if (!((iterObj->get()->IsActive()) && (iterObj->get()->IsEnable())))
		{
			continue;
		}

		(*iterObj).get()->PreUpdate(Deltatime);
	}

	std::list<std::shared_ptr<CSceneComponent>>::iterator iterComponent = mComponentList.begin();
	std::list<std::shared_ptr<CSceneComponent>>::iterator iterComponentEnd = mComponentList.end();

	for (; iterComponent != iterComponentEnd; iterComponent++)
	{
		if (!((iterComponent->get()->IsActive()) && (iterComponent->get()->IsEnable())))
		{
			continue;
		}

		(*iterComponent).get()->PreUpdate(Deltatime);
	}
}

void CSceneObject::Update(float Deltatime)
{
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObj = mChildObjList.begin();
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObjEnd = mChildObjList.end();

	for (; iterObj != iterObjEnd; iterObj++)
	{
		if (!((iterObj->get()->IsActive()) && (iterObj->get()->IsEnable())))
		{
			continue;
		}
		(*iterObj).get()->Update(Deltatime);
	}

	std::list<std::shared_ptr<CSceneComponent>>::iterator iterComponent = mComponentList.begin();
	std::list<std::shared_ptr<CSceneComponent>>::iterator iterComponentEnd = mComponentList.end();

	for (; iterComponent != iterComponentEnd; iterComponent++)
	{
		if (!((iterComponent->get()->IsActive()) && (iterComponent->get()->IsEnable())))
		{
			continue;
		}
		(*iterComponent).get()->Update(Deltatime);
	}
}

void CSceneObject::PostUpdate(float Deltatime)
{
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObj = mChildObjList.begin();
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObjEnd = mChildObjList.end();

	for (; iterObj != iterObjEnd; iterObj++)
	{
		if (!((iterObj->get()->IsActive()) && (iterObj->get()->IsEnable())))
		{
			continue;
		}
		(*iterObj).get()->PostUpdate(Deltatime);
	}

	std::list<std::shared_ptr<CSceneComponent>>::iterator iterComponent = mComponentList.begin();
	std::list<std::shared_ptr<CSceneComponent>>::iterator iterComponentEnd = mComponentList.end();

	for (; iterComponent != iterComponentEnd; iterComponent++)
	{
		if (!((iterComponent->get()->IsActive()) && (iterComponent->get()->IsEnable())))
		{
			continue;
		}
		(*iterComponent).get()->PostUpdate(Deltatime);
	}
}

void CSceneObject::Collision(float Deltatime)
{
	std::list<std::shared_ptr<CSceneComponent>>::iterator iterComponent = mComponentList.begin();
	std::list<std::shared_ptr<CSceneComponent>>::iterator iterComponentEnd = mComponentList.end();

	for (; iterComponent != iterComponentEnd; iterComponent++)
	{
		if (!((iterComponent->get()->IsActive()) && (iterComponent->get()->IsEnable())))
		{
			continue;
		}

		(*iterComponent).get()->Collision(Deltatime);
	}
}

void CSceneObject::PreRender(float DeltaTime)
{
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObj = mChildObjList.begin();
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObjEnd = mChildObjList.end();

	for (; iterObj != iterObjEnd; iterObj++)
	{
		if (!((iterObj->get()->IsActive()) && (iterObj->get()->IsEnable())))
		{
			continue;
		}
		(*iterObj).get()->PreRender(DeltaTime);
	}

	std::list<std::shared_ptr<CSceneComponent>>::iterator iterComponent = mComponentList.begin();
	std::list<std::shared_ptr<CSceneComponent>>::iterator iterComponentEnd = mComponentList.end();

	for (; iterComponent != iterComponentEnd; iterComponent++)
	{
		if (!((iterComponent->get()->IsActive()) && (iterComponent->get()->IsEnable())))
		{
			continue;
		}
		(*iterComponent).get()->PreRender(DeltaTime);
	}
}

void CSceneObject::Render()
{
	std::list<std::shared_ptr<CSceneComponent>>::iterator iterComponent = mComponentList.begin();
	std::list<std::shared_ptr<CSceneComponent>>::iterator iterComponentEnd = mComponentList.end();

	for (; iterComponent != iterComponentEnd; iterComponent++)
	{
		if (!((iterComponent->get()->IsActive()) && (iterComponent->get()->IsEnable())))
		{
			continue;
		}
		(*iterComponent).get()->Render();
	}
}

void CSceneObject::PostRender()
{
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObj = mChildObjList.begin();
	std::list<std::shared_ptr<CSceneObject>>::iterator iterObjEnd = mChildObjList.end();

	for (; iterObj != iterObjEnd; iterObj++)
	{
		if (!((iterObj->get()->IsActive()) && (iterObj->get()->IsEnable())))
		{
			continue;
		}
		(*iterObj).get()->PostRender();
	}

	std::list<std::shared_ptr<CSceneComponent>>::iterator iterComponent = mComponentList.begin();
	std::list<std::shared_ptr<CSceneComponent>>::iterator iterComponentEnd = mComponentList.end();

	for (; iterComponent != iterComponentEnd; iterComponent++)
	{
		if (!((iterComponent->get()->IsActive()) && (iterComponent->get()->IsEnable())))
		{
			continue;
		}
		(*iterComponent).get()->PostRender();
	}

	// 삭제

	for (iterObj = mChildObjList.begin(); iterObj != iterObjEnd;)
	{
		if (!(iterObj->get()->IsActive()))
		{
			iterObj = mChildObjList.erase(iterObj);
			iterObjEnd = mChildObjList.end();
			continue;
		}
		++iterObj;
	}

	for (iterComponent = mComponentList.begin(); iterComponent != iterComponentEnd;)
	{
		if (!(iterComponent->get()->IsActive()))
		{
			iterComponent = mComponentList.erase(iterComponent);
			iterComponentEnd = mComponentList.end();
			continue;
		}
		++iterComponent;
	}
}

CSceneObject* CSceneObject::Clone()
{
	return new CSceneObject(*this);
}