#include "ColliderBase.h"

#include "../Object/SceneObject.h"
#include "TransformComponent.h"

#include "../Shader/ConstantBuffer/TransformCBuffer.h"
#include "../Shader/ShaderManager.h"
#include "../Scene/Scene.h"
#include "../Asset/Mesh/Mesh.h"
#include "../Asset/AssetManager.h"

CColliderBase::CColliderBase()
{
}

CColliderBase::~CColliderBase()
{
}

bool CColliderBase::Init()
{
	if (!CSceneComponent::Init())
	{
		return false;
	}

	mCenter = FVector3D(0.f, 0.f, 0.f);
	mSize = FVector3D(0.f, 0.f, 0.f);
	
	mTransform = std::dynamic_pointer_cast<CTransformComponent>(mParentObj.lock()->FindComponent("Transform").lock());
	if (mTransform.expired())
	{
		return false;
	}

	mColliderSurface = EColliderSurface::None;

#ifdef _DEBUG

	mShader = CShaderManager::GetInstance().FindShader("FrameMeshShader");
	mMesh = CAssetManager::GetInstance().GetMeshManager()->FindMesh("FrameCenterRect");

	mTransformBuffer = std::make_shared<TransformCBuffer>();
	mTransformBuffer->Init();

#endif
	return true;
}

void CColliderBase::Render()
{
	CSceneComponent::Render();

//#ifdef _DEBUG
//	FMatrix matScale, matRot, matTranslate, matWorld;
//	matScale.Scaling(mSize);
//
//	matTranslate.Translation(mCenter);
//
//	matWorld = matScale * matRot * matTranslate;
//
//	mTransformBuffer->SetWorldMatrix(matWorld);
//	mTransformBuffer->SetViewMatrix(mScene.lock()->GetCamera()->GetViewMatrix());
//	mTransformBuffer->SetProjMatrix(mScene.lock()->GetCamera()->GetProjMatrix());
//
//	mTransformBuffer->UpdateBuffer();
//
//	mShader.lock()->SetShader();
//
//	mMesh.lock()->Render();
//#endif
}

void CColliderBase::PostRender()
{
	CollisionObjList.clear();
}

void CColliderBase::Collision(float Deltatime)
{
}

bool CColliderBase::CheckCollision(std::shared_ptr<CColliderBase> collider,float DeltaTime)
{
	return false;
}

void CColliderBase::UpdateTransform()
{
	mCenter = mTransform.lock()->GetWorldPosition();
	mSize = mTransform.lock()->GetWorldScale();

	mMin = mCenter - (mSize/2);
	mMax = mCenter + (mSize/2);
}
