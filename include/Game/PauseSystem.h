#pragma once

#include "../Object/SceneObject.h"

class PauseSystem : public CSceneObject
{
public:
    bool Init() override;

public:
    void SwitchPause(float DeltaTime);

protected:
    bool IsPause = false;

    void Pause();
    void UnPause();
};

