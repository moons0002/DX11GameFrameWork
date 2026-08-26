#include "PauseSystem.h"

#include "../Scene/Scene.h"
#include "../GameManager.h"

#include "PauseScreen.h"

bool PauseSystem::Init()
{
	mScene.lock()->GetInput()->AddBindFunction('P', EInputType::Down, 
		shared_from_this(), &PauseSystem::SwitchPause);

    return true;
}

void PauseSystem::SwitchPause(float DeltaTime)
{
	IsPause = !IsPause;
	CGameManager::GetInstance().SwitchPause();

	if (IsPause)
	{
		Pause();
	}
	else
	{
		UnPause();
	}
}

void PauseSystem::Pause()
{
	mScene.lock()->CreateObject<PauseScreen>("PauseScreen");
	std::dynamic_pointer_cast<PauseScreen>(mScene.lock()->FindObject("PauseScreen").lock())->InitScreenCount(3);
}

void PauseSystem::UnPause()
{
	mScene.lock()->FindObject("PauseScreen").lock()->Destroy();
}
