#pragma once

#include "../Gameinfo.h"

class CSceneObject;
class CRenderStateManager;

class CRenderManager
{
private:
	std::shared_ptr<CRenderStateManager> mStateManager = nullptr;

	std::list<std::weak_ptr<CSceneObject>> mRenderList;
	std::list<std::weak_ptr<CSceneObject>> mUIRenderList;

public:
	std::shared_ptr<CRenderStateManager> GetStateManager()
	{
		return mStateManager;
	}
	void PushBackRenderList(std::weak_ptr<CSceneObject> Comp);
	
	void PushBackUIRenderList(std::weak_ptr<CSceneObject> Comp);

public:
	bool Init();
	void Render();

	void ClearRenderList();

public:
	private:
	CRenderManager();
	~CRenderManager();
	CRenderManager(const CRenderManager&) = delete;
	void operator=(const CRenderManager&) = delete;

public:
	static CRenderManager &GetInstance() {
		static CRenderManager inst;
		return inst;
	}

};

