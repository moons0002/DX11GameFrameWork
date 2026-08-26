#pragma once

#include "../Object/SceneObject.h"

class Door : public CSceneObject
{
public:
	bool Init() override;

protected:
	// 이 문은 어느 좌표로 이동시켜 주는가
	FVector2D ToPosition;
	// 이 문이 작동되면 어느 Stage로 변경할까
	std::string ToStage;
	
public:
	void SetToPosition(FVector2D Position);
	FVector2D GetToPosition();

	void SetToStage(std::string Stage);
	std::string& GetToStage();
};