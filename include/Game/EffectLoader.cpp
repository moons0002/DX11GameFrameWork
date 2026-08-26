#include "EffectLoader.h"

#include "../Asset/AssetManager.h"

bool EffectLoader::Init()
{
	std::shared_ptr<CEffectManager> EffectManager = CAssetManager::GetInstance().GetEffectManager();

	EffectManager->AddAnimation("Effect", "BeamEffect1", "BeamWaveCollision1", FVector2D(0.f, 0.f), FVector2D(80.f, 80.f), FVector2D(0.f, 0.f), 6, 1);
	EffectManager->ChangeState("BeamWaveCollision1");
	EffectManager->SetPlayOption(FAnimationPlayOption::Once);
	EffectManager->SetSpeed(100);

	EffectManager->AddAnimation("Effect", "BeamEffect1", "BeamWaveCollision2", FVector2D(0.f, 80.f), FVector2D(80.f, 80.f), FVector2D(0.f, 0.f), 5, 1);
	EffectManager->ChangeState("BeamWaveCollision2");
	EffectManager->SetPlayOption(FAnimationPlayOption::LoopAB);
	EffectManager->SetSpeed(100);
	EffectManager->SetRepeatIndex(1);
	
	EffectManager->AddAnimation("Effect", "BeamEffect1", "BeamWaveCollision3", FVector2D(0.f, 160.f), FVector2D(80.f, 80.f), FVector2D(0.f, 0.f), 9, 1);
	EffectManager->ChangeState("BeamWaveCollision3");
	EffectManager->SetPlayOption(FAnimationPlayOption::Once);
	EffectManager->SetSpeed(100);

	return true;
}