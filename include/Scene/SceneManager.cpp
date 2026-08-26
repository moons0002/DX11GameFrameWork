#include "SceneManager.h"

// 여기 수정
#include "../Game/StageScene.h"

bool CSceneManager::Init()
{
	// 여기 수정
	if (!CreateScene<StageScene>("MainScene"))
	{
		return false;
	}

	mCurrentScene = FindScene("MainScene").lock();

	if (mCurrentScene == nullptr)
	{
		return false;
	}
	return true;
}

void CSceneManager::Input(float DeltaTime)
{
	mCurrentScene->Input(DeltaTime);
}

void CSceneManager::Update(float DeltaTime)
{
	mCurrentScene->PreUpdate(DeltaTime);
	mCurrentScene->Update(DeltaTime);
	mCurrentScene->PostUpdate(DeltaTime);
}

void CSceneManager::Collision(float DeltaTime)
{
	mCurrentScene->Collision(DeltaTime);
}

void CSceneManager::Render(float DeltaTime)
{
	mCurrentScene->PreRender(DeltaTime);
	mCurrentScene->Render();
	mCurrentScene->PostRender();
}

std::weak_ptr<CScene> CSceneManager::FindScene(const std::string & Name)
{
	std::unordered_map<std::string, std::shared_ptr<CScene>>::iterator iter = mSceneMap.find(Name);
	if (iter == mSceneMap.end())
	{
		return std::weak_ptr<CScene>();
	}
	return iter->second;
}

std::weak_ptr<CScene> CSceneManager::GetCurrentScene()
{
	return mCurrentScene;
}

void CSceneManager::ChangeScene(const std::string& Name)
{
	std::weak_ptr<CScene> Scene = FindScene(Name);

}

CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{
}