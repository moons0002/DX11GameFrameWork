#include "SceneComponent.h"
#include "../Scene/Scene.h"


CSceneComponent::CSceneComponent()
{
}

CSceneComponent::~CSceneComponent()
{
}

bool CSceneComponent::Init()
{
	return true;
}

void CSceneComponent::PreUpdate(float Deltatime)
{
}

void CSceneComponent::Update(float Deltatime)
{
}

void CSceneComponent::PostUpdate(float Deltatime)
{
}

void CSceneComponent::Collision(float Deltatime)
{
}

void CSceneComponent::PreRender(float DeltaTime)
{
}

void CSceneComponent::Render()
{
}

void CSceneComponent::PostRender()
{
}

CSceneComponent* CSceneComponent::Clone()
{
	return new CSceneComponent(*this);
}