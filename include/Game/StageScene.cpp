#include "StageScene.h"

#include "KirbyObject.h"
#include "BrontoBurtEnemy.h"
#include "BeamEnemy.h"

#include "BackGround.h"
#include "Stage_1_1.h"
#include "Stage_1_1_0.h"

#include "KirbyHP.h"
#include "StageIcon.h"
#include "BottomScreen.h"
#include "AbilityIcon.h"
#include "AbilityName.h"
#include "KirbyLifeIcon.h"
#include "KirbyLifeCount.h"
#include "ScoreLetter.h"
#include "ScoreCount.h"
#include "FadeInOut.h"

#include "TextureLoader.h"
#include "EffectLoader.h"

#include "../Asset/AssetManager.h"
#include "PauseSystem.h"

#include "../Component/TransformComponent.h"

bool StageScene::Init()
{
	CScene::Init();

	TextureLoader Textures;
	Textures.Init();
	EffectLoader Effects;
	Effects.Init();

	// 오브젝트
	CreateObject<KirbyObject>("Kirby");
	CreateObject<FadeInOut>("FadeInOut");

	// UI (오브젝트)
	CreateObject<KirbyHP>("KirbyHP");
	CreateObject<StageIcon>("StageIcon");
	CreateObject<BottomScreen>("BottomScreen");
	CreateObject<AbilityIcon>("AbilityIcon");
	CreateObject<AbilityName>("AbilityName");
	CreateObject<KirbyLifeIcon>("KirbyLifeIcon");
	CreateObject<KirbyLifeCount>("KirbyLifeCount_0");
	CreateObject<KirbyLifeCount>("KirbyLifeCount_1");
	CreateObject<ScoreLetter>("ScoreLetter");
	CreateObject<ScoreCount>("ScoreCount");

	// 백그라운드
	CreateObject<BackGround>("BackGround");
	// Pause
	CreateObject<PauseSystem>("PauseSystem");

	std::dynamic_pointer_cast<CAnimationComponent>(FindObject("FadeInOut").lock()->FindComponent("Animation").lock())->SetOpacity(0, 1.f);
	StartChangeStage("Stage_1_1", FVector2D(-400.f, -20.f));

	// 카메라 타겟 설정
	SetCameraTarget(FindObject("Kirby").lock());

	return true;
}

void StageScene::PreRender(float DeltaTime)
{
	CScene::PreRender(DeltaTime);

	AddScore((int)(1234 * DeltaTime));

	if (IsChangingStage)
	{
		ChangeStageTimeSum += DeltaTime;
		if (ChangeStageTime <= ChangeStageTimeSum)
		{
			ChangeStage();
		}
	}
}

void StageScene::PostRender()
{
	CScene::PostRender();

	std::vector<std::weak_ptr<CEnemyObject>>::iterator iterObj = mEnemyList.begin();
	std::vector<std::weak_ptr<CEnemyObject>>::iterator iterObjEnd = mEnemyList.end();

	/// 삭제

	for (; iterObj != iterObjEnd;)
	{
		if (iterObj->expired())
		{
			iterObj = mEnemyList.erase(iterObj);
			iterObjEnd = mEnemyList.end();
			continue;
		}
		if (!(iterObj->lock()->IsActive()))
		{
			iterObj = mEnemyList.erase(iterObj);
			iterObjEnd = mEnemyList.end();
			continue;
		}
		++iterObj;
	}
}

void StageScene::AddEnemy(std::weak_ptr<CEnemyObject> Enemy)
{
	mEnemyList.push_back(Enemy);
}

void StageScene::AddScore(int Score)
{
	mScore += Score;
}

void StageScene::SetScore(int Score)
{
	mScore = Score;
}

int StageScene::GetScore()
{
	return mScore;
}

void StageScene::RemoveEnemy()
{
	auto iter = mObjList.begin();
	auto iterEnd = mObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->get()->GetObjectType() == ObjectType::Enemy)
		{
			iter->get()->Destroy();
		}
	}
}

void StageScene::RemoveMap()
{
	auto iter = mObjList.begin();
	auto iterEnd = mObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->get()->GetObjectType() == ObjectType::Map)
		{
			iter->get()->Destroy();
		}
	}
}

void StageScene::StartChangeStage(std::string StageName, FVector2D Position)
{
	IsChangingStage = true;
	ToStage = StageName;
	ToPosition = Position;
	std::dynamic_pointer_cast<FadeInOut>(FindObject("FadeInOut").lock())->FadeOut(1.f);
}

void StageScene::ChangeToStage_1_1_0()
{
	RemoveEnemy();
	RemoveMap();

	// 적
	CreateObject<BeamEnemy>("Beam_1");
	auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindObject("Beam_1").lock()->FindComponent("Transform").lock());
	Transform->SetLocalPos(30.f, -30.f, 0.f);

	// 맵
	CreateObject<Stage_1_1_0>("Stage_1_1_0");

	// 적 추가
	AddEnemy(std::dynamic_pointer_cast<CEnemyObject>(FindObject("Beam_1").lock()));

	SetSize(FVector2D(264.f, 216.f));
}

void StageScene::ChangeToStage_1_1()
{
	RemoveEnemy();
	RemoveMap();

	//
	std::dynamic_pointer_cast<CTransformComponent>(FindObject("Kirby").lock()->FindComponent("Transform").lock())->SetLocalPos(SpawnPoint);

	// 적
	CreateObject<BrontoBurtEnemy>("BrontoBurt_0");
	CreateObject<BrontoBurtEnemy>("BrontoBurt_1");
	CreateObject<BeamEnemy>("Beam_0");

	// 맵
	CreateObject<Stage_1_1>("Stage_1_1");

	// 적 추가
	AddEnemy(std::dynamic_pointer_cast<CEnemyObject>(FindObject("BrontoBurt_0").lock()));
	AddEnemy(std::dynamic_pointer_cast<CEnemyObject>(FindObject("BrontoBurt_1").lock()));
	AddEnemy(std::dynamic_pointer_cast<CEnemyObject>(FindObject("Beam_0").lock()));

	std::dynamic_pointer_cast<CTransformComponent>(FindObject("BrontoBurt_0").lock()->FindComponent("Transform").lock())->SetLocalPos(-200.f, -10.f, 0.f);
	std::dynamic_pointer_cast<CTransformComponent>(FindObject("BrontoBurt_1").lock()->FindComponent("Transform").lock())->SetLocalPos(0.f, -20.f, 0.f);
	std::dynamic_pointer_cast<CTransformComponent>(FindObject("Beam_0").lock()->FindComponent("Transform").lock())->SetLocalPos(-350.f, -20.f, 0.f);

	// 맵 사이즈
	SetSize(FVector2D(888.f, 216.f));
}

void StageScene::ChangeStage()
{
	if (ToStage == "Stage_1_1_0")
	{
		ChangeToStage_1_1_0();
	}
	else if (ToStage == "Stage_1_1")
	{
		ChangeToStage_1_1();
	}
	SpawnPoint = ToPosition;
	std::dynamic_pointer_cast<CTransformComponent>((FindObject("Kirby").lock()->FindComponent("Transform").lock()))->SetLocalPos(ToPosition);
	IsChangingStage = false;
	ChangeStageTimeSum = 0.f;
	std::dynamic_pointer_cast<FadeInOut>(FindObject("FadeInOut").lock())->FadeIn(1.f);
}
