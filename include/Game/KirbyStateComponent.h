#pragma once

#include "../Component/SceneComponent.h"

#include "InhalableEnemyObject.h"
#include "InhaleComponent.h"
#include "KirbyObject.h"

class CTransformComponent;
class CAnimationComponent;

struct FKirbyKeyState
{
    bool KeyDown = false;
    bool KeyHold = false;
    bool KeyUp = false;
};

class KirbyStateComponent : public CSceneComponent
{
protected:
	std::weak_ptr<CTransformComponent> mTransformComponent;
    std::weak_ptr<CAnimationComponent> mAnimationComponent;
    std::weak_ptr<CInhaleComponent> mInhaleComponent;

    std::string mKirbyState;
    EKirbyAbility mKirbyAbility;

    std::string mAbilityName;

    // 이동속도
    float mSpeed = 40.f;
    float mJumpSpeed = 150.f;
    float mAirSpeed = -50.f;
    float mAirUpSpeed = 100.f;

    // 키 저장
    std::map<std::string, std::shared_ptr<FKirbyKeyState>> mKeyMap;

    bool IsGround = false;

    bool LookingRight = true;

    bool FixLooking = false;

    bool IsHolding = false;

    bool IsInhaling = false;
    
    bool mIsGod = false;

    bool mGetInput = true;

    EInhalableEnemyType HoldingType = EInhalableEnemyType::None;

protected:
    float Time = 0.f;
    float PrevKeyDownTime = 0.f;

    float JumpTime = 0.4f;
    float JumpStartTime = 0.f;

    float HoldingJumpTime = 0.5f;
    float HoldingJumpStartTime = 0.f;

    float AirUpTime = 0.5f;
    float AirUpStartTime = 0.f;

    float AirEndTime = 0.2f;
    float AirEndStartTime = 0.f;
    
    float DamageTime = 1.f;
    float DamageStartTime = 0.f;

    // Normal
    float InhaleTime = 1.f;
    float InhaleStartTime = 0.f;

    float SpitTime = 0.5f;
    float SpitStartTime = 0.f;

    float SwallowTime = 0.6f;
    float SwallowStartTime = 0.f;

    // Beam
    float BeamChargeTime = 1.f;
    float BeamChargeStartTime = 0.f;
    
    float BeamWhipTime = 1.f;
    float BeamWhipStartTime = 0.f;

    float BeamWaveTime = 0.2f;
    float BeamWaveStartTime = 0.f;

    std::string PrevKey;

protected:
    void RightKeyDown(float DeltaTime);
    void RightKeyHold(float DeltaTime);
    void RightKeyUp(float DeltaTime);

    void LeftKeyDown(float DeltaTime);
    void LeftKeyHold(float DeltaTime);
    void LeftKeyUp(float DeltaTime);

    void DownKeyDown(float DeltaTime);
    void DownKeyHold(float DeltaTime);
    void DownKeyUp(float DeltaTime);

    void UpKeyDown(float DeltaTime);
    void UpKeyHold(float DeltaTime);
    void UpKeyUp(float DeltaTime);

    void JumpKeyDown(float DeltaTime);
    void JumpKeyHold(float DeltaTime);
    void JumpKeyUp(float DeltaTime);

    void InhaleKeyDown(float DeltaTime);
    void InhaleKeyHold(float DeltaTime);
    void InhaleKeyUp(float DeltaTime);

public:
    bool Init() override;

    void Update(float DeltaTime) override;
    void PreRender(float DeltaTime) override;

protected:
    void CheckCondition();

    void LookingCondition();
    void IdleCondition();
    void WalkCondition();
    void RunCondition();
    void DownCondition();
    void JumpCondition();
    void FlyCondition();
    void AirCondition();
    void AirUpCondition();
    void AirEndCondition();

    void InhaleCondition();
    void HoldingIdleCondition();
    void HoldingWalkCondition();
    void HoldingJumpCondition();
    void HoldingFlyCondition();
    void SwallowCondition();
    void SpitCondition();

    void BeamChargeCondition();
    void BeamWhipCondition();
    void BeamWaveCondition();

    void DamageCondition();

public:
    void UpdateData();

public:
    void OnGround();
    void NotOnGround();

    void HoldingIn(EInhalableEnemyType Type);
    void NotHoldingIn();

    bool IsGod();

    bool IsLookingRight();

public:
    void StopAndInhale();
    
    void ChangeAbility();

    void Damaged();
};

