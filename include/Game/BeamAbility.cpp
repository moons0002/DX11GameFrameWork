#include "BeamAbility.h"

#include "KirbyObject.h"
#include "KirbyStateComponent.h"

#include "../Component/TransformComponent.h"

#include "BeamWaveCenter.h"
#include "../Scene/Scene.h"

bool BeamAbility::Init()
{
	CreateComponent<CTransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());

	return true;
}

void BeamAbility::PostUpdate(float DeltaTime)
{
	CSceneObject::PostUpdate(DeltaTime);

	CurState = std::dynamic_pointer_cast<KirbyObject>(mParentObj.lock())->GetState();

	if (PrevState == "Charge")
	{
		IsLookingRight = std::dynamic_pointer_cast<KirbyStateComponent>(mParentObj.lock()->FindComponent("KirbyState").lock())->IsLookingRight();
		if (std::dynamic_pointer_cast<KirbyStateComponent>(mParentObj.lock()->FindComponent("KirbyState").lock())->IsLookingRight())
		{
			// 회전 시켜줘서 자연스럽게 반대편에 나오도록?
		}
		if (CurState == "Whip")
		{
			BeamWhipStart();
		}
		else if (CurState == "Wave")
		{
			BeamWaveStart();
		}
	}

	PrevState = CurState;
}

void BeamAbility::BeamWhipStart()
{
	// 어떻게 할까 BeamWhip을 5개 생성해서
}

void BeamAbility::BeamWaveStart()
{
	mScene.lock()->CreateObject<BeamWaveCenter>("BeamWaveCenter_" + std::to_string(++count));

	auto BeamWaveCenterTransform = std::dynamic_pointer_cast<CTransformComponent>(mScene.lock()->FindObject("BeamWaveCenter_" + std::to_string(count)).lock()->FindComponent("Transform").lock());

	BeamWaveCenterTransform->SetLocalScale(16.f, 16.f, 1.f);
	if (IsLookingRight)
	{
		BeamWaveCenterTransform->SetLocalPos(std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock())->GetWorldPosition() + FVector3D(30.f, 0.f, 0.f));
		BeamWaveCenterTransform->SetVelocityX(BeamWaveSpeed);
	}
	else
	{
		BeamWaveCenterTransform->SetLocalPos(std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock())->GetWorldPosition() + FVector3D(-30.f, 0.f, 0.f));
		BeamWaveCenterTransform->SetVelocityX(-BeamWaveSpeed);
		BeamWaveCenterTransform->SetLocalRotationZ(180.f);
	}

	IsBeamWave = true;
}
