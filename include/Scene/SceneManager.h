#pragma once

#include "../GameInfo.h"
#include "Scene.h"

class CSceneManager
{
private:
	std::shared_ptr<CScene> mCurrentScene = nullptr;
	std::unordered_map<std::string, std::shared_ptr<CScene>> mSceneMap;

public:
	bool Init();
	void Input(float DeltaTime);
	void Update(float DeltaTime);
	void Collision(float DeltaTime);
	void Render(float DeltaTime);

public:
	template <typename T>
	bool CreateScene(const std::string& Name)
	{
		std::shared_ptr<CScene> Scene = FindScene(Name).lock();

		if (Scene)
		{
			return true;
		}

		Scene = std::make_shared<T>();

		if (!Scene->Init())
		{
			return false;
		}

		mSceneMap.insert(std::make_pair(Name, Scene));

		return true;
	}

	std::weak_ptr<CScene> FindScene(const std::string& Name);
	std::weak_ptr<CScene> GetCurrentScene();
	void ChangeScene(const std::string& Name);

private:
	CSceneManager();
	~CSceneManager();

public:
	static CSceneManager& GetInstance() {
		static CSceneManager inst;
		return inst;
	}

};