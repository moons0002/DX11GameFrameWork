#pragma once
#include "../Object/SceneObject.h"

enum EInhalableEnemyType;

enum class EKirbyAbility
{
    None,
    Beam
};

class KirbyObject :  public CSceneObject
{
public:
    bool Init();
    
    void PostUpdate(float DeltaTime) override;

    void Collision(float DeltaTime) override;

public:
    void ChangeAbility(EInhalableEnemyType EnemyType);

    EKirbyAbility GetAbility();

    std::string& GetAnimationName();

    std::string& GetState();
    void SetState(std::string State);

    void AddHp(float Hp);
    float GetHp();

    void SetLife(int Life);
    void AddLife(int Life);
    int GetLife();

protected:
    EKirbyAbility Ability = EKirbyAbility::None;
    std::string AnimationName = "";

    std::string mState;

    float mHp = 100.f;
    int mLife = 3;

protected:
    void BeamInit();
    void ChangeBeam();
};