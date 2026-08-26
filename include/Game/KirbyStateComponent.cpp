#include "KirbyStateComponent.h"

#include "../Object/SceneObject.h"
#include "../Component/TransformComponent.h"
#include "../Component/AnimationComponent.h"
#include "../Scene/Scene.h"

#include "DoorComponent.h"

bool KirbyStateComponent::Init()
{
    mTransformComponent = std::dynamic_pointer_cast<CTransformComponent>(mParentObj.lock()->FindComponent("Transform").lock());
	mAnimationComponent = std::dynamic_pointer_cast<CAnimationComponent>(mParentObj.lock()->FindComponent("Animation").lock());
	mInhaleComponent = std::dynamic_pointer_cast<CInhaleComponent>(mParentObj.lock()->FindComponent("Inhale").lock());

	if (mTransformComponent.expired() || mAnimationComponent.expired() || mInhaleComponent.expired())
		return false;

	mKeyMap.emplace(std::make_pair("Right", std::make_shared<FKirbyKeyState>()));
	mKeyMap.emplace(std::make_pair("Left", std::make_shared<FKirbyKeyState>()));
	mKeyMap.emplace(std::make_pair("Down", std::make_shared<FKirbyKeyState>()));
	mKeyMap.emplace(std::make_pair("Up", std::make_shared<FKirbyKeyState>()));
	mKeyMap.emplace(std::make_pair("Jump", std::make_shared<FKirbyKeyState>()));
	mKeyMap.emplace(std::make_pair("Inhale", std::make_shared<FKirbyKeyState>()));

	mAbilityName = std::dynamic_pointer_cast<KirbyObject>(mParentObj.lock())->GetAnimationName();

	mScene.lock()->GetInput()->AddBindFunction('D', EInputType::Down, 
		shared_from_this(), &KirbyStateComponent::RightKeyDown);
	mScene.lock()->GetInput()->AddBindFunction('D', EInputType::Hold, 
		shared_from_this(), &KirbyStateComponent::RightKeyHold);
	mScene.lock()->GetInput()->AddBindFunction('D', EInputType::Up, 
		shared_from_this(), &KirbyStateComponent::RightKeyUp);

	mScene.lock()->GetInput()->AddBindFunction('A', EInputType::Down, 
		shared_from_this(), &KirbyStateComponent::LeftKeyDown);
	mScene.lock()->GetInput()->AddBindFunction('A', EInputType::Hold, 
		shared_from_this(), &KirbyStateComponent::LeftKeyHold);
	mScene.lock()->GetInput()->AddBindFunction('A', EInputType::Up, 
		shared_from_this(), &KirbyStateComponent::LeftKeyUp);

	mScene.lock()->GetInput()->AddBindFunction('S', EInputType::Down, 
		shared_from_this(), &KirbyStateComponent::DownKeyDown);
	mScene.lock()->GetInput()->AddBindFunction('S', EInputType::Hold, 
		shared_from_this(), &KirbyStateComponent::DownKeyHold);
	mScene.lock()->GetInput()->AddBindFunction('S', EInputType::Up, 
		shared_from_this(), &KirbyStateComponent::DownKeyUp);

	mScene.lock()->GetInput()->AddBindFunction('W', EInputType::Down, 
		shared_from_this(), &KirbyStateComponent::UpKeyDown);
	mScene.lock()->GetInput()->AddBindFunction('W', EInputType::Hold, 
		shared_from_this(), &KirbyStateComponent::UpKeyHold);
	mScene.lock()->GetInput()->AddBindFunction('W', EInputType::Up, 
		shared_from_this(), &KirbyStateComponent::UpKeyUp);

	mScene.lock()->GetInput()->AddBindFunction('J', EInputType::Down, 
		shared_from_this(), &KirbyStateComponent::JumpKeyDown);
	mScene.lock()->GetInput()->AddBindFunction('J', EInputType::Hold, 
		shared_from_this(), &KirbyStateComponent::JumpKeyHold);
	mScene.lock()->GetInput()->AddBindFunction('J', EInputType::Up, 
		shared_from_this(), &KirbyStateComponent::JumpKeyUp);

	mScene.lock()->GetInput()->AddBindFunction('N', EInputType::Down, 
		shared_from_this(), &KirbyStateComponent::InhaleKeyDown);
	mScene.lock()->GetInput()->AddBindFunction('N', EInputType::Hold, 
		shared_from_this(), &KirbyStateComponent::InhaleKeyHold);
	mScene.lock()->GetInput()->AddBindFunction('N', EInputType::Up, 
		shared_from_this(), &KirbyStateComponent::InhaleKeyUp);

    return true;
}

void KirbyStateComponent::RightKeyDown(float DeltaTime)
{
	mKeyMap["Right"]->KeyDown = true;
}

void KirbyStateComponent::RightKeyHold(float DeltaTime)
{
	mKeyMap["Right"]->KeyHold = true;
}

void KirbyStateComponent::RightKeyUp(float DeltaTime)
{
	mKeyMap["Right"]->KeyUp = true;
}

void KirbyStateComponent::LeftKeyDown(float DeltaTime)
{
	mKeyMap["Left"]->KeyDown = true;
}

void KirbyStateComponent::LeftKeyHold(float DeltaTime)
{
	mKeyMap["Left"]->KeyHold = true;
}

void KirbyStateComponent::LeftKeyUp(float DeltaTime)
{
	mKeyMap["Left"]->KeyUp = true;
}

void KirbyStateComponent::DownKeyDown(float DeltaTime)
{
	mKeyMap["Down"]->KeyDown = true;
}

void KirbyStateComponent::DownKeyHold(float DeltaTime)
{
	mKeyMap["Down"]->KeyHold = true;
}

void KirbyStateComponent::DownKeyUp(float DeltaTime)
{
	mKeyMap["Down"]->KeyUp = true;
}

void KirbyStateComponent::UpKeyDown(float DeltaTime)
{
	std::dynamic_pointer_cast<DoorComponent>(mParentObj.lock()->FindComponent("Door").lock())->CheckDoor();
	mKeyMap["Up"]->KeyDown = true;
}

void KirbyStateComponent::UpKeyHold(float DeltaTime)
{
	mKeyMap["Up"]->KeyHold = true;
}

void KirbyStateComponent::UpKeyUp(float DeltaTime)
{
	mKeyMap["Up"]->KeyUp = true;
}

void KirbyStateComponent::JumpKeyDown(float DeltaTime)
{
	mKeyMap["Jump"]->KeyDown = true;
}

void KirbyStateComponent::JumpKeyHold(float DeltaTime)
{
	mKeyMap["Jump"]->KeyHold = true;
}

void KirbyStateComponent::JumpKeyUp(float DeltaTime)
{
	mKeyMap["Jump"]->KeyUp = true;
}

void KirbyStateComponent::InhaleKeyDown(float DeltaTime)
{
	mKeyMap["Inhale"]->KeyDown = true;
}

void KirbyStateComponent::InhaleKeyHold(float DeltaTime)
{
	mKeyMap["Inhale"]->KeyHold = true;
}

void KirbyStateComponent::InhaleKeyUp(float DeltaTime)
{
	mKeyMap["Inhale"]->KeyUp = true;
}

void KirbyStateComponent::Update(float DeltaTime)
{
	Time += DeltaTime;
	// 현재 상태를 받아온다
	mKirbyState = std::dynamic_pointer_cast<KirbyObject>(mParentObj.lock())->GetState();
	mKirbyAbility = std::dynamic_pointer_cast<KirbyObject>(mParentObj.lock())->GetAbility();
	// 현재 상태에 따라 상태 전환
	CheckCondition();
	// 현재 상태 저장
	std::dynamic_pointer_cast<KirbyObject>(mParentObj.lock())->SetState(mKirbyState);
	// 현재 상태에 따라서 물리 값 조정
	UpdateData();

	// 상태 초기화
	for (auto o : mKeyMap)
	{
		if (o.second->KeyDown == true)
		{
			PrevKey = o.first;
			PrevKeyDownTime = Time;
			o.second->KeyDown = false;
		}

		if (o.second->KeyUp == true)
		{
			o.second->KeyHold = false;
			o.second->KeyUp = false;
		}
	}
}

void KirbyStateComponent::PreRender(float DeltaTime)
{
	if (LookingRight)
		mAnimationComponent.lock()->SetFlip(false, false);
	else
		mAnimationComponent.lock()->SetFlip(true, false);

	switch (std::dynamic_pointer_cast<KirbyObject>(mParentObj.lock())->GetAbility())
	{
	case EKirbyAbility::Beam:
		mKirbyState = "Beam" + mKirbyState;
		break;
	default:
		break;
	}
	mAnimationComponent.lock()->ChangeState(mKirbyState);
}

void KirbyStateComponent::CheckCondition()
{
	if (!FixLooking) LookingCondition();

	if (mKirbyState == "Idle")
	{
		IdleCondition();
	}
	else if (mKirbyState == "Walk")
	{
		WalkCondition();
	}
	else if (mKirbyState == "Run")
	{
		RunCondition();
	}
	else if (mKirbyState == "Down")
	{
		DownCondition();
	}
	else if (mKirbyState == "Jump")
	{
		JumpCondition();
	}
	else if (mKirbyState == "Fly")
	{
		FlyCondition();
	}
	else if (mKirbyState == "Air")
	{
		AirCondition();
	}
	else if (mKirbyState == "AirUp")
	{
		AirUpCondition();
	}
	else if (mKirbyState == "AirEnd")
	{
		AirEndCondition();
	}
	else if (mKirbyState == "Inhale")
	{
		InhaleCondition();
	}
	else if (mKirbyState == "HoldingIdle")
	{
		HoldingIdleCondition();
	}
	else if (mKirbyState == "HoldingWalk")
	{
		HoldingWalkCondition();
	}
	else if (mKirbyState == "HoldingJump")
	{
		HoldingJumpCondition();
	}
	else if (mKirbyState == "HoldingFly")
	{
		HoldingFlyCondition();
	}
	else if (mKirbyState == "Swallow")
	{
		SwallowCondition();
	}
	else if (mKirbyState == "Spit")
	{
		SpitCondition();
	}
	else if (mKirbyState == "Damage")
	{
		DamageCondition();
	}
	else if (mKirbyState == "Charge")
	{
		BeamChargeCondition();
	}
	else if (mKirbyState == "Whip")
	{
		BeamWhipCondition();
	}
	else if (mKirbyState == "Wave")
	{
		BeamWaveCondition();
	}
}

void KirbyStateComponent::LookingCondition()
{
	if (mKeyMap["Right"]->KeyDown)
		LookingRight = true;
	else if (mKeyMap["Left"]->KeyDown)
		LookingRight = false;
	else if (!mKeyMap["Right"]->KeyHold && mKeyMap["Left"]->KeyHold)
		LookingRight = false;
	else if (!mKeyMap["Left"]->KeyHold && mKeyMap["Right"]->KeyHold)
		LookingRight = true;
}

// 여기는 모든 능력의 공통부 (이곳에서 Inhale키를 누를때는 반드시 현재 상태를 확인하고 알맞은 상태로 변경한다)
void KirbyStateComponent::IdleCondition()
{
	// 공중에 있는가
	if (!IsGround)
	{
		mKirbyState = "Fly";
		return;
	}

	// 특정 키를 눌렀는가
	// 이 부분은 공통 부분임
	if (mKeyMap["Right"]->KeyDown)
	{
		if (LookingRight && PrevKey == "Right" && (Time - PrevKeyDownTime) <= 0.3)
		{
			mKirbyState = "Run";
		}
		else
		{
			mKirbyState = "Walk";
		}
	}
	else if (mKeyMap["Left"]->KeyDown)
	{
		if (!LookingRight && PrevKey == "Left" && (Time - PrevKeyDownTime) <= 0.3)
		{
			mKirbyState = "Run";
		}
		else
		{
			mKirbyState = "Walk";
		}
	}
	else if (mKeyMap["Down"]->KeyDown)
	{
		mKirbyState = "Down";
	}
	else if (mKeyMap["Jump"]->KeyDown)
	{
		mKirbyState = "Jump";
	}

	// 일반 커비의 고유한 능력이라서 None일때만 일로가야함..
	else if (mKeyMap["Inhale"]->KeyDown && mKirbyAbility == EKirbyAbility::None)
	{
		mKirbyState = "Inhale";
	}
	// 그 밑에는 빔 커비만의 전환을 추가해주자..
	else if (mKeyMap["Inhale"]->KeyDown && mKirbyAbility == EKirbyAbility::Beam)
	{
		mKirbyState = "Charge";
	}
	// 특정 키를 누르고 있었는가
	else if (mKeyMap["Right"]->KeyHold)
	{
		if (LookingRight && PrevKey == "Right" && (Time - PrevKeyDownTime) <= 0.3)
		{
			mKirbyState = "Run";
		}
		else
		{
			mKirbyState = "Walk";
		}
	}
	else if (mKeyMap["Left"]->KeyHold)
	{
		if (!LookingRight && PrevKey == "Left" && (Time - PrevKeyDownTime) <= 0.3)
		{
			mKirbyState = "Run";
		}
		else
		{
			mKirbyState = "Walk";
		}
	}
	else if (mKeyMap["Down"]->KeyHold)
	{
		mKirbyState = "Down";
	}
	// 일반 커비만의 고유한 능력
	else if (mKeyMap["Inhale"]->KeyHold && mKirbyAbility == EKirbyAbility::None)
	{
		mKirbyState = "Inhale";
	}
}

void KirbyStateComponent::WalkCondition()
{
	if (!IsGround)
	{
		mKirbyState = "Fly";
		return;
	}

	if (mKeyMap["Down"]->KeyDown)
	{
		mKirbyState = "Down";
	}
	else if (mKeyMap["Jump"]->KeyDown)
	{
		mKirbyState = "Jump";
	}
	else if (mKeyMap["Inhale"]->KeyDown && mKirbyAbility == EKirbyAbility::None)
	{
		mKirbyState = "Inhale";
	}
	else if (mKeyMap["Inhale"]->KeyDown && mKirbyAbility == EKirbyAbility::Beam)
	{
		mKirbyState = "Charge";
	}

	else if ((mKeyMap["Right"]->KeyUp && LookingRight) || (mKeyMap["Left"]->KeyUp && !LookingRight))
	{
		mKirbyState = "Idle";

		if (mKeyMap["Down"]->KeyHold)
		{
			mKirbyState = "Down";
		}
		else if (mKeyMap["Inhale"]->KeyHold && mKirbyAbility == EKirbyAbility::None)
		{
			mKirbyState = "Inhale";
		}
	}
}

void KirbyStateComponent::RunCondition()
{
	if (!IsGround)
	{
		mKirbyState = "Fly";
		return;
	}

	if (mKeyMap["Down"]->KeyDown)
	{
		mKirbyState = "Down";
	}
	else if (mKeyMap["Jump"]->KeyDown)
	{
		mKirbyState = "Jump";
	}
	else if (mKeyMap["Inhale"]->KeyDown && mKirbyAbility == EKirbyAbility::None)
	{
		mKirbyState = "Inhale";
	}

	else if ((mKeyMap["Right"]->KeyUp && LookingRight) || (mKeyMap["Left"]->KeyUp && !LookingRight))
	{
		mKirbyState = "Idle";

		if (mKeyMap["Down"]->KeyHold)
		{
			mKirbyState = "Down";
		}
		else if (mKeyMap["Inhale"]->KeyHold && mKirbyAbility == EKirbyAbility::None)
		{
			mKirbyState = "Inhale";
		}
	}
}

void KirbyStateComponent::DownCondition()
{
	if (!IsGround)
	{
		mKirbyState = "Fly";
		return;
	}

	if (mKeyMap["Right"]->KeyDown)
	{
		if (LookingRight && PrevKey == "Right" && (Time - PrevKeyDownTime) <= 0.3)
		{
			mKirbyState = "Run";
		}
		else
		{
			mKirbyState = "Walk";
		}
	}
	else if (mKeyMap["Left"]->KeyDown)
	{
		if (!LookingRight && PrevKey == "Left" && (Time - PrevKeyDownTime) <= 0.3)
		{
			mKirbyState = "Run";
		}
		else
		{
			mKirbyState = "Walk";
		}
	}
	else if (mKeyMap["Jump"]->KeyDown)
	{
		mKirbyState = "Jump";
	}
	else if (mKeyMap["Inhale"]->KeyDown && mKirbyAbility == EKirbyAbility::None)
	{
		mKirbyState = "Inhale";
	}
	else if (mKeyMap["Inhale"]->KeyDown && mKirbyAbility == EKirbyAbility::Beam)
	{
		mKirbyState = "Charge";
	}

	else if (mKeyMap["Down"]->KeyUp)
	{
		if (mKeyMap["Right"]->KeyDown)
		{
			if (LookingRight && PrevKey == "Right" && (Time - PrevKeyDownTime) <= 0.3)
			{
				mKirbyState = "Run";
			}
			else
			{
				mKirbyState = "Walk";
			}
		}
		else if (mKeyMap["Left"]->KeyDown)
		{
			if (!LookingRight && PrevKey == "Left" && (Time - PrevKeyDownTime) <= 0.3)
			{
				mKirbyState = "Run";
			}
			else
			{
				mKirbyState = "Walk";
			}
		}
		else if (mKeyMap["Inhale"]->KeyDown && mKirbyAbility == EKirbyAbility::None)
		{
			mKirbyState = "Inhale";
		}
		else if (mKeyMap["Inhale"]->KeyHold && mKirbyAbility == EKirbyAbility::None)
		{
			mKirbyState = "Inhale";
		}
		else
		{
			mKirbyState = "Idle";
		}
	}
}

void KirbyStateComponent::JumpCondition()
{
	if (JumpTime <= Time - JumpStartTime)
	{
		mKirbyState = "Fly";
		JumpStartTime = 0.f;
	}
	else if (mKeyMap["Jump"]->KeyDown)
	{
		mKirbyState = "AirUp";
	}
	else if (mKeyMap["Inhale"]->KeyDown && mKirbyAbility == EKirbyAbility::None)
	{
		mKirbyState = "Inhale";
	}
}

void KirbyStateComponent::FlyCondition()
{
	if (IsGround)
	{
		mKirbyState = "Idle";
	}
	else if (mKeyMap["Jump"]->KeyDown)
	{
		mKirbyState = "AirUp";	
	}
	else if (mKeyMap["Inhale"]->KeyDown && mKirbyAbility == EKirbyAbility::None)
	{
		mKirbyState = "Inhale";
	}
}

void KirbyStateComponent::AirCondition()
{
	if (IsGround)
	{
		mKirbyState = "AirEnd";
	}
	else if (mKeyMap["Jump"]->KeyDown)
	{
		mKirbyState = "AirUp";	
	}
	else if (mKeyMap["Inhale"]->KeyDown)
	{
		mKirbyState = "AirEnd";
	}
}

void KirbyStateComponent::AirUpCondition()
{
	if (IsGround)
	{
		mKirbyState = "AirEnd";
	}
	if (mKeyMap["Jump"]->KeyDown && AirUpTime * 0.75 <= (Time - AirUpStartTime))
	{
		AirUpStartTime = 0.f;
	}
	else if (AirUpTime <= Time - AirUpStartTime)
	{
		mKirbyState = "Air";
		AirUpStartTime = 0.f;
	}
	else if (mKeyMap["Inhale"]->KeyDown && mKirbyAbility == EKirbyAbility::None)
	{
		mKirbyState = "AirEnd";
	}
}

void KirbyStateComponent::AirEndCondition()
{
	if (AirEndTime <= Time - AirEndStartTime)
	{
		mKirbyState = "Idle";
		AirEndStartTime = 0.f;
	}
}

void KirbyStateComponent::DamageCondition()
{
	if (DamageTime <= Time - DamageStartTime)
	{
		mKirbyState = "Idle";
		DamageStartTime = 0;
		FixLooking = false;
		mIsGod = false;
	}
}

// 여기부터는 기본 커비만의 능력
void KirbyStateComponent::InhaleCondition()
{
	// 적이 빨려들어 오는중
	if (IsInhaling)
	{
		// 적을 먹었다면
		if (IsHolding)
		{
			IsInhaling = false;
			mKirbyState = "HoldingIdle";
		}
	}
	else if (mKeyMap["Right"]->KeyDown)
	{
		if (LookingRight && PrevKey == "Right" && (Time - PrevKeyDownTime) <= 0.3)
		{
			mKirbyState = "Run";
		}
		else
		{
			mKirbyState = "Walk";
		}
	}
	else if (mKeyMap["Left"]->KeyDown)
	{
		if (!LookingRight && PrevKey == "Left" && (Time - PrevKeyDownTime) <= 0.3)
		{
			mKirbyState = "Run";
		}
		else
		{
			mKirbyState = "Walk";
		}
	}
	else if (mKeyMap["Down"]->KeyDown)
	{
		mKirbyState = "Down";
	}
	else if (mKeyMap["Jump"]->KeyDown)
	{
		mKirbyState = "Jump";
	}
	else if (mKeyMap["Inhale"]->KeyUp)
	{
		mKirbyState = "Idle";
	}
	else if (mKeyMap["Inhale"]->KeyHold)
	{
		return;
	}
	mInhaleComponent.lock()->StopInhale();
	FixLooking = false;
}

void KirbyStateComponent::HoldingIdleCondition()
{
	// 공중에 있는가
	if (!IsGround)
	{
		mKirbyState = "HoldingFly";
		return;
	}

	// 특정 키를 눌렀는가
	if (mKeyMap["Right"]->KeyDown || mKeyMap["Left"]->KeyDown)
	{
		mKirbyState = "HoldingWalk";
	}
	else if (mKeyMap["Down"]->KeyDown)
	{
		mKirbyState = "Swallow";
	}
	else if (mKeyMap["Jump"]->KeyDown)
	{
		mKirbyState = "HoldingJump";
	}
	else if (mKeyMap["Inhale"]->KeyDown)
	{
		mKirbyState = "Spit";
	}

	// 특정 키를 누르고 있었는가
	else if (mKeyMap["Right"]->KeyHold || mKeyMap["Left"]->KeyHold)
	{
		mKirbyState = "HoldingWalk";
	}
}

void KirbyStateComponent::HoldingWalkCondition()
{
	if (!IsGround)
	{
		mKirbyState = "HoldingFly";
		return;
	}

	if (mKeyMap["Jump"]->KeyDown)
	{
		mKirbyState = "HoldingJump";
	}
	else if (mKeyMap["Down"]->KeyDown)
	{
		mKirbyState = "Swallow";
	}
	else if (mKeyMap["Inhale"]->KeyDown)
	{
		mKirbyState = "Spit";
	}

	else if ((mKeyMap["Right"]->KeyUp && LookingRight) || (mKeyMap["Left"]->KeyUp && !LookingRight))
	{
		mKirbyState = "HoldingIdle";
	}
}

void KirbyStateComponent::HoldingJumpCondition()
{
	if (HoldingJumpTime <= Time - HoldingJumpStartTime)
	{
		mKirbyState = "HoldingFly";
		HoldingJumpStartTime = 0.f;
	}
	else if (mKeyMap["Inhale"]->KeyDown)
	{
		mKirbyState = "Spit";
	}
}

void KirbyStateComponent::HoldingFlyCondition()
{
	if (IsGround)
	{
		mKirbyState = "HoldingIdle";
	}
	else if (mKeyMap["Inhale"]->KeyDown)
	{
		mKirbyState = "Spit";
	}
}

void KirbyStateComponent::SwallowCondition()
{
	if (SwallowTime <= Time - SwallowStartTime)
	{
		ChangeAbility();
		mKirbyState = "Idle";
		SwallowStartTime = 0.f;
	}
}

void KirbyStateComponent::SpitCondition()
{
	if (SpitTime <= Time - SpitStartTime)
	{
		mKirbyState = "Idle";
		SpitStartTime = 0.f;
	}
}

// 여기에는 빔 커비만의 능력을 추가시켜주자

void KirbyStateComponent::BeamChargeCondition()
{
	if (mKeyMap["Inhale"]->KeyUp)
	{
		if (BeamChargeTime <= Time - BeamChargeStartTime)
		{
			mKirbyState = "Wave";
			BeamWaveStartTime = Time;
		}
		else
		{
			mKirbyState = "Whip";
			BeamWhipStartTime = Time;
		}
	}
}

void KirbyStateComponent::BeamWhipCondition()
{
	if (BeamWhipTime <= Time - BeamWhipStartTime)
	{
		mKirbyState = "Idle";
		BeamWhipStartTime = 0.f;
	}
}

void KirbyStateComponent::BeamWaveCondition()
{
	if (BeamWaveTime <= Time - BeamWaveStartTime)
	{
		mKirbyState = "Idle";
		BeamWaveStartTime = 0.f;
	}
}


void KirbyStateComponent::UpdateData()
{
	if (mKirbyState == "Walk" || mKirbyState == "HoldingWalk")
	{
		if (LookingRight)
			mTransformComponent.lock()->SetVelocityX(mSpeed);
		else
			mTransformComponent.lock()->SetVelocityX(-mSpeed);
	}
	else if (mKirbyState == "Run")
	{
		if (LookingRight)
			mTransformComponent.lock()->SetVelocityX(mSpeed * 2);
		else
			mTransformComponent.lock()->SetVelocityX(-mSpeed * 2);
	}
	else if (mKirbyState == "Jump" && mKeyMap["Jump"]->KeyDown && JumpStartTime == 0.f)
	{
		mTransformComponent.lock()->SetVelocityY(mJumpSpeed);
		JumpStartTime = Time;
	}
	else if (mKirbyState == "AirUp" && mKeyMap["Jump"] && AirUpStartTime == 0.f)
	{
		mTransformComponent.lock()->SetVelocityY(mAirUpSpeed);
		AirUpStartTime = Time;
	}
	else if (mKirbyState == "AirEnd" && AirEndStartTime == 0.f)
	{
		mTransformComponent.lock()->SetVelocityY(0.f);
		AirEndStartTime = Time;
	}
	else if (mKirbyState == "HoldingJump" && mKeyMap["Jump"]->KeyDown && HoldingJumpStartTime == 0.f)
	{
		mTransformComponent.lock()->SetVelocityY(mJumpSpeed);
		HoldingJumpStartTime = Time;
	}
	else if (mKirbyState == "Swallow" && mKeyMap["Down"]->KeyDown && SwallowStartTime == 0.f)
	{
		IsHolding = false;
		SwallowStartTime = Time;
	}
	else if (mKirbyState == "Spit" && mKeyMap["Inhale"]->KeyDown && SpitStartTime == 0.f)
	{
		IsHolding = false;
		SpitStartTime = Time;
	}
	else if (mKirbyState == "Jump" || mKirbyState == "Fly" || mKirbyState == "Air" || mKirbyState == "AirUp" || mKirbyState == "HoldingJump" || mKirbyState == "HoldingFly")
	{
		if (mKeyMap["Right"]->KeyHold && LookingRight)
			mTransformComponent.lock()->SetVelocityX(mSpeed);
		else if (mKeyMap["Left"]->KeyHold && !LookingRight)
			mTransformComponent.lock()->SetVelocityX(-mSpeed);
		else
			mTransformComponent.lock()->SetVelocityX(0.f);

		if (mKirbyState == "Air")
			mTransformComponent.lock()->SetVelocityY(mAirSpeed);
	}
	else if (mKirbyState == "Inhale" && mKeyMap["Inhale"]->KeyDown)
	{
		mInhaleComponent.lock()->StartInhale(LookingRight);
		FixLooking = true;
	}
	else if (mKirbyState == "Charge" && mKeyMap["Inhale"]->KeyDown)
	{
		BeamChargeStartTime = Time;
	}
	else if (mKirbyState == "Damage")
	{
		;
	}
	else
	{
		mTransformComponent.lock()->SetVelocityX(0.f);
		mTransformComponent.lock()->SetAccelerationX(0.f);
	}
}

void KirbyStateComponent::OnGround()
{
	IsGround = true;
}

void KirbyStateComponent::NotOnGround()
{
	IsGround = false;
}

void KirbyStateComponent::HoldingIn(EInhalableEnemyType Type)
{
	IsHolding = true;
	HoldingType = Type;
}

void KirbyStateComponent::NotHoldingIn()
{
	IsHolding = false;
	HoldingType = EInhalableEnemyType::None;
}

bool KirbyStateComponent::IsGod()
{
	return mIsGod;
}

bool KirbyStateComponent::IsLookingRight()
{
	return LookingRight;
}

void KirbyStateComponent::StopAndInhale()
{
	IsInhaling = true;
}

void KirbyStateComponent::ChangeAbility()
{
	std::dynamic_pointer_cast<KirbyObject>(mParentObj.lock())->ChangeAbility(HoldingType);
	mKirbyAbility = std::dynamic_pointer_cast<KirbyObject>(mParentObj.lock())->GetAbility();
}

void KirbyStateComponent::Damaged()
{
	if (mTransformComponent.lock()->GetVelocity().x < 0)
		mTransformComponent.lock()->SetAccelerationX(25.f);
	else
		mTransformComponent.lock()->SetAccelerationX(-25.f);

	FixLooking = true;
	mIsGod = true;

	DamageStartTime = Time;
}
