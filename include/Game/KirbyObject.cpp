#include "KirbyObject.h"

#include "../Component/AnimationComponent.h"
#include "../Component/TransformComponent.h"
#include "InhaleComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"

#include "InhalableEnemyObject.h"
#include "KirbyStateComponent.h"
#include "KirbyDamage.h"
#include "DoorComponent.h"

#include "../Component/GravityComponent.h"
#include "../Component/MovementConstraintComponent.h"
#include "BeamAbility.h"

#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"


bool KirbyObject::Init()
{
	mObjectType = ObjectType::Kirby;

	// Transform
	CreateComponent<CTransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());
	Transform->SetLocalScale(24.f, 24.f, 1.f);

	CreateComponent<CColliderAABB2D>("Collider");
	auto Collider = std::dynamic_pointer_cast<CColliderAABB2D>(FindComponent("Collider").lock());
	Collider->UpdateTransform();
	mScene.lock()->AddCollider(Collider);

	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	// Kirby라는 이름의 텍스처를 사용할것이다
	Animation->SetTexture("Kirby");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(10);
	
	// 1. 기본
	Animation->AddAnimation("Kirby", "Idle", FVector2D(0.f, 0.f), FVector2D(40.f, 40.f), FVector2D(0.f, 0.f), 15, 1);
	Animation->ChangeState("Idle", 0);
	
	//Animation->SetPivot(0.f, -2.f);
	Animation->SetPlayOption(FAnimationPlayOption::Loop);
	Animation->SetSpeed(40);

	// 2. 걷기
	Animation->AddAnimation("Kirby", "Walk",FVector2D(0,120.f), FVector2D(40.f, 40.f), FVector2D(0.f,0.f), 10, 1);
	Animation->ChangeState("Walk", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Loop);
	Animation->SetSpeed(40);

	// 3. Run
	Animation->AddAnimation("Kirby", "Run", FVector2D(0, 200.f), FVector2D(40.f, 40.f), FVector2D(0.f,0.f), 8, 1);
	Animation->ChangeState("Run", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Loop);
	Animation->SetSpeed(40);

	// 4. 아래 키
	Animation->AddAnimation("Kirby", "Down", FVector2D(0, 40.f), FVector2D(40.f, 40.f), FVector2D(0.f,0.f), 15 ,1);
	Animation->ChangeState("Down", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Loop);
	Animation->SetSpeed(40);

	// 5. 흡수 중
	Animation->AddAnimation("Kirby", "Inhale", FVector2D(0.f, 280.f), FVector2D(40.f, 40.f), FVector2D(0.f,0.f), 4 ,1);
	Animation->ChangeState("Inhale", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::PingPong);
	Animation->SetSpeed(70);

	// 6. 먹은채로 가만히
	Animation->AddAnimation("Kirby", "HoldingIdle", FVector2D(0.f, 80.f), FVector2D(40.f, 40.f), FVector2D(0.f,0.f), 15 ,1);
	Animation->ChangeState("HoldingIdle", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Loop);
	Animation->SetSpeed(40);

	// 7. 삼키기
	Animation->AddAnimation("Kirby", "Swallow", FVector2D(0.f, 320.f), FVector2D(40.f, 40.f), FVector2D(0.f,0.f), 7 ,1);
	Animation->ChangeState("Swallow", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(40);

	// 8. 먹은채로 걷기
	Animation->AddAnimation("Kirby", "HoldingWalk", FVector2D(0.f, 160.f), FVector2D(40.f, 40.f), FVector2D(0.f,0.f), 10 ,1);
	Animation->ChangeState("HoldingWalk", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Loop);
	Animation->SetSpeed(40);

	// 9. 점프
	Animation->AddAnimation("Kirby", "Jump", FVector2D(0.f, 240.f), FVector2D(40.f, 40.f), FVector2D(0.f,0.f), 7 ,1);
	Animation->ChangeState("Jump", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(60);

	// 9.01 삼킨채 점프
	Animation->AddAnimation("KirbyJump2", "HoldingJump", FVector2D(35.f, 0.f), FVector2D(34.f, 40.f), FVector2D(0.f,0.f), 4 ,1);
	Animation->ChangeState("HoldingJump", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(40);

	// 9.02 삼킨채 떨어지기
	Animation->AddAnimation("KirbyJump2", "HoldingFly", FVector2D(169.f, 0.f), FVector2D(36.f, 40.f), FVector2D(0.f,0.f), 2 ,1);
	Animation->ChangeState("HoldingFly", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Loop);
	Animation->SetSpeed(40);

	// 9.1 날기
	Animation->AddAnimation("Kirby", "Fly", FVector2D(280.f, 240.f), FVector2D(40.f, 40.f), FVector2D(0.f,0.f), 2 ,1);
	Animation->ChangeState("Fly", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Loop);
	Animation->SetSpeed(40);

	// 9.2 공기날기
	Animation->AddAnimation("KirbyAir", "Air", FVector2D(2.f, 40.f), FVector2D(35.f, 40.f), FVector2D(0.f,0.f), 3 ,1);
	Animation->ChangeState("Air", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Loop);
	Animation->SetSpeed(40);

	// 9.3 공기 올라가기
	Animation->AddAnimation("KirbyAir", "AirUp", FVector2D(35.f * 3.f + 3.f, 40.f), FVector2D(35.f, 40.f), FVector2D(0.f,0.f), 3 ,1);
	Animation->ChangeState("AirUp", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::PingPong);
	Animation->SetSpeed(40);

	// 9.4 공기 착지
	Animation->AddAnimation("KirbyAir", "AirEnd", FVector2D(0.f, 0.f), FVector2D(30.f, 40.f), FVector2D(0.f,0.f), 4 ,1);
	Animation->ChangeState("AirEnd", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(80);

	// 10. 뱉기
	Animation->AddAnimation("Kirby", "Spit", FVector2D(0.f, 360.f), FVector2D(40.f, 40.f), FVector2D(0.f,0.f), 5 ,1);
	Animation->ChangeState("Spit", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(40);

	BeamInit();

	// 11. 데미지
	Animation->AddAnimation("KirbyDamage", "Damage", FVector2D(0.f, 0.f), FVector2D(32.f, 32.f), FVector2D(0.f,0.f), 1 ,1);
	Animation->ChangeState("Damage", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(0);

	// 시작할 애니메이션 변경
	Animation->ChangeState("Idle");
	mState = "Idle";

	// StateComponent
	CreateComponent<CInhaleComponent>("Inhale");
	CreateComponent<KirbyStateComponent>("KirbyState");
	CreateComponent<GravityComponent>("Gravity");
	CreateComponent<MovementConstraintComponent>("MovementConstraint");
	CreateComponent<KirbyDamage>("KirbyDamage");
	CreateComponent<DoorComponent>("Door");
	
	CreateChildObject<BeamAbility>("BeamAbility");

	return true;
}

void KirbyObject::PostUpdate(float DeltaTime)
{
	CSceneObject::PostUpdate(DeltaTime);
}

void KirbyObject::Collision(float DeltaTime)
{
	CSceneObject::Collision(DeltaTime);
}

void KirbyObject::BeamInit()
{
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	// Idle
	Animation->AddAnimation("BeamKirby", "BeamIdle", FVector2D(0.f, 0.f), FVector2D(48.f, 48.f), FVector2D(0.f, 0.f), 15, 1);
	Animation->ChangeState("BeamIdle", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Loop);
	Animation->SetSpeed(40);

	// Walk
	Animation->AddAnimation("BeamKirby", "BeamWalk", FVector2D(0.f, 48.f * 2.f), FVector2D(48.f, 48.f), FVector2D(0.f, 0.f), 12, 1);
	Animation->ChangeState("BeamWalk", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Loop);
	Animation->SetSpeed(40);

	// Run
	Animation->AddAnimation("BeamKirby", "BeamRun", FVector2D(0.f, 48.f * 3.f), FVector2D(48.f, 48.f), FVector2D(0.f, 0.f), 8, 1);
	Animation->ChangeState("BeamRun", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Loop);
	Animation->SetSpeed(40);

	// Down
	Animation->AddAnimation("BeamKirby", "BeamDown", FVector2D(0, 48.f * 1.f), FVector2D(48.f, 48.f), FVector2D(0.f,0.f), 15 ,1);
	Animation->ChangeState("BeamDown", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Loop);
	Animation->SetSpeed(40);

	// Jump
	Animation->AddAnimation("BeamKirby", "BeamJump", FVector2D(0.f, 48.f * 4.f), FVector2D(48.f, 48.f), FVector2D(0.f, 0.f), 8, 1);
	Animation->ChangeState("BeamJump", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(40);

	// Fly
	Animation->AddAnimation("BeamKirby", "BeamFly", FVector2D(48.f * 8.f, 48.f * 4.f - 2.f), FVector2D(48.f, 48.f + 4.f), FVector2D(0.f,0.f), 2 ,1);
	Animation->ChangeState("BeamFly", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Loop);
	Animation->SetSpeed(40);

	// Air
	Animation->AddAnimation("BeamKirby2", "BeamAir", FVector2D(157.f, 0.f), FVector2D(32.f, 48.f), FVector2D(0.f,0.f), 3 ,1);
	Animation->ChangeState("BeamAir", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Loop);
	Animation->SetSpeed(40);

	// AirUp
	Animation->AddAnimation("BeamKirby2", "BeamAirUp", FVector2D(254.f, 0.f), FVector2D(33.f, 48.f), FVector2D(0.f,0.f), 3 ,1);
	Animation->ChangeState("BeamAirUp", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::PingPong);
	Animation->SetSpeed(40);

	// 9.4 공기 착지
	Animation->AddAnimation("BeamKirby2", "BeamAirEnd", FVector2D(0.f, 0.f), FVector2D(31.f, 48.f), FVector2D(0.f,0.f), 5 ,1);
	Animation->ChangeState("BeamAirEnd", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(40);

	// 모으기
	Animation->AddAnimation("BeamKirby3", "BeamCharge", FVector2D(0.f, 0.f), FVector2D(40.f, 48.f), FVector2D(0.f,0.f), 1 ,1);
	Animation->ChangeState("BeamCharge", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(40);

	// 일반 빔 (채찍 빔)
	Animation->AddAnimation("BeamKirby3", "BeamWhip", FVector2D(80.f, 0.f), FVector2D(40.f, 48.f), FVector2D(0.f,0.f), 7 ,1);
	Animation->ChangeState("BeamWhip", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(40);

	// 차지 빔 (웨이브 빔)
	Animation->AddAnimation("BeamKirby3", "BeamWave", FVector2D(40.f, 0.f), FVector2D(40.f, 48.f), FVector2D(0.f,0.f), 1 ,1);
	Animation->ChangeState("BeamWave", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(40);
}

void KirbyObject::ChangeAbility(EInhalableEnemyType EnemyType)
{
	switch(EnemyType)
	{
	case EInhalableEnemyType::None:
		break;
	case EInhalableEnemyType::Beam:
		ChangeBeam();
		break;
		return;
	default:
		break;
	}
}

EKirbyAbility KirbyObject::GetAbility()
{
	return Ability;
}

std::string & KirbyObject::GetAnimationName()
{
	return AnimationName;
}

std::string& KirbyObject::GetState()
{
	return mState;
}

void KirbyObject::SetState(std::string State)
{
	mState = State;
}

void KirbyObject::AddHp(float Hp)
{
	mHp += Hp;
	if (mHp <= 0.f) mHp = 0.f;
	if (mHp >= 100.f) mHp = 100.f;
}

float KirbyObject::GetHp()
{
	return mHp;
}

void KirbyObject::SetLife(int Life)
{
	mLife = Life;
}

void KirbyObject::AddLife(int Life)
{
	mLife += Life;
}

int KirbyObject::GetLife()
{
	return mLife;
}

void KirbyObject::ChangeBeam()
{
	Ability = EKirbyAbility::Beam;
	AnimationName = "Beam";
}