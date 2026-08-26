#pragma once

#include "../Scene/Scene.h"

class CSceneObject;
class CEnemyObject;

class StageScene : public CScene
{
protected:
	int mScore = 0;

	std::vector<std::weak_ptr<CEnemyObject>> mEnemyList;

	FVector2D ToPosition;
	bool IsChangingStage = false;
	std::string ToStage;

	float ChangeStageTime = 0.5f;
	float ChangeStageTimeSum = 0.f;

	FVector2D SpawnPoint;

public:
	bool Init() override;

	void PreRender(float DeltaTime) override;

	void PostRender() override;

public:

	virtual void AddEnemy(std::weak_ptr<CEnemyObject> Enemy);
	
	std::vector<std::weak_ptr<CEnemyObject>> GetEnemyList()
	{
		return mEnemyList;
	}

	void AddScore(int Score);
	void SetScore(int Score);
	int GetScore();

public:
	void RemoveEnemy();
	void RemoveMap();

	void StartChangeStage(std::string StageName, FVector2D Position) override;

	void ChangeToStage_1_1_0();
	void ChangeToStage_1_1();

protected:
	void ChangeStage();
};