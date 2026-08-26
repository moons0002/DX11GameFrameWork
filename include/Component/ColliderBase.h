#pragma once

#include "SceneComponent.h"

class CTransformComponent;

enum class EColliderType
{
    Collider2D,
    Collider3D
};

enum class EColliderShape
{
    AABB2D,
    Sphere2D,
    OBB2D,
    Line2D
};

enum class EColliderSurface
{
    Ground,
    Wall,
    Ceiling,
    Pass,
    None
};

class CColliderBase : public CSceneComponent
{
public:
    CColliderBase();
    virtual ~CColliderBase();

protected:
    EColliderType mColliderType;
    EColliderShape mColliderShape;
    EColliderSurface mColliderSurface;

    FVector3D mCenter;
    FVector3D mSize;

    FVector3D mMin;
    FVector3D mMax;

    std::string mChannel = "Default";

    std::vector<std::weak_ptr<CColliderBase>> CollisionObjList;

    std::weak_ptr<CTransformComponent> mTransform;

#ifdef _DEBUG
    std::shared_ptr<class TransformCBuffer> mTransformBuffer = nullptr;
  
    std::weak_ptr<class CShader> mShader;
	std::weak_ptr<class CMesh> mMesh;
#endif

public:
    EColliderType GetColliderType()
    {
        return mColliderType;
    }
    EColliderShape GetColliderShape()
    {
        return mColliderShape;
    }
    EColliderSurface GetColliderSurface()
    {
        return mColliderSurface;
    }

    FVector3D& GetCenter()
    {
        return mCenter;
    }
    FVector3D& GetMin()
    {
        return mMin;
    }
    FVector3D& GetMax()
    {
        return mMax;
    }

    std::string& GetChannel()
	{
		return mChannel;
	}
    std::vector<std::weak_ptr<CColliderBase>>& GetCollisionObjList()
    {
        return CollisionObjList;
    }

    void SetColliderSurface(EColliderSurface Surface)
    {
        mColliderSurface = Surface;
    }

    void SetCenter(const FVector3D& center)
    {
        mCenter = center;
    }
    void SetSize(const FVector3D& size)
    {
        mSize = size;
    }

    bool Init() override;

    void Render() override;
    void PostRender() override;

    void Collision(float DeltaTime);

    virtual bool CheckCollision(std::shared_ptr<CColliderBase> collider, float DeltaTime);

    virtual void UpdateTransform();
};

