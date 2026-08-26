#pragma once

#include "../Object/SceneObject.h"

class BeamAbility : public CSceneObject
{
public:
	bool Init() override;

	void PostUpdate(float DeltaTime) override;
// 빔 오브젝트를 미리 생성시켜놓고 !Enable상태로 바꿔놓기
// 
// 1. 커비의 상태가 Update단계에서 변경되므로, PostUpdate때 확인해서 작동되도록.
// 2. 이 오브젝트를 Enable상태로 변경보다는 얘는 계속 살아있는게 좋을듯?
// 3. 그리고 시작함수 같은거를 만들어서 시작되도록

// 4. 밑에 작은 빔 구성요소를 만들어서 그 빔들이 적당히 움직일수 있도록 하자
// 5. 차라리 이 친구를 매니저로 만든다??

protected:
	std::string CurState;
	std::string PrevState;

	bool IsLookingRight; 
	bool IsBeamWave = false;
	bool IsBeamWhip = false;

	int count = 0;

	float BeamWaveSpeed = 80.f;

protected:
	void BeamWhipStart();
	void BeamWaveStart();

};

