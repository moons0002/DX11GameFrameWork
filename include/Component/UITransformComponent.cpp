#include "UITransformComponent.h"

#include "../Shader/ConstantBuffer/TransformCBuffer.h"

#include "../Scene/Scene.h"
#include "../Component/AnimationComponent.h"

void UITransformComponent::PreRender(float DelatTime)
{
}

void UITransformComponent::Render()
{
	mTransformCBuffer->UpdateBuffer();
}

void UITransformComponent::UpdateMatrix()
{
	if (IsUsingTextureScale) 
	{
		mAnimationSize = std::dynamic_pointer_cast<CAnimationComponent>(mParentObj.lock()->FindComponent("Animation").lock())->GetAnimationSize();
		mmatScale.Scaling(mWorldScale * FVector3D(mAnimationSize.x, mAnimationSize.y, 1.f));
	}
	else
	{
		mmatScale.Scaling(mWorldScale);
	}

	mmatRot.Rotation(mWorldRot);
	mmatTranslate.Translation(mWorldPos);
	
	mmatWorld = mmatScale * mmatRot * mmatTranslate;

	mTransformCBuffer->SetWorldMatrix(mmatWorld);
	mTransformCBuffer->SetViewMatrix(mScene.lock()->GetUICamera()->GetViewMatrix());
	mTransformCBuffer->SetProjMatrix(mScene.lock()->GetUICamera()->GetProjMatrix());
}
