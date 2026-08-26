#pragma once

#include "../Object/SceneObject.h"

class PauseScreen : public CSceneObject
{
public:
    bool Init() override;

    void Update(float DeltaTime) override;

    void PostUpdate(float DeltaTime) override;

protected:
    int mPrevScreen;
    int mCurScreen;
    int mNextScreen;

    int mIndexCount;

    bool IsMoving = false;

    bool MoveRight = false;
    bool MoveLeft = false;

    float MoveTime = 0.5f;

    bool IsCreateScreens = false;

public:
    void InitScreenCount(int Count);

    void CreateScreens(FVector3D Position, std::string Name);

    void MoveScreenLeft(float DeltaTime);
    void MoveScreenRight(float DeltaTime);
};

