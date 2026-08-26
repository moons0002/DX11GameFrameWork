#include "PauseScreen.h"

#include "../Component/AnimationComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderLine2D.h"
#include "../Component/MapColliderAABB2D.h"

#include "../GameManager.h"
#include "../Asset/AssetManager.h"

#include "../Scene/Scene.h"

#include "PauseObject.h"
#include "PausePrevNextPage.h"

bool PauseScreen::Init()
{
	mScene.lock()->GetInput()->AddBindFunction('A', EInputType::Down, 
		shared_from_this(), &PauseScreen::MoveScreenLeft);
	mScene.lock()->GetInput()->AddBindFunction('D', EInputType::Down, 
		shared_from_this(), &PauseScreen::MoveScreenRight);

	// Transform
	CreateComponent<CTransformComponent>("Transform");
	auto Transform = std::dynamic_pointer_cast<CTransformComponent>(FindComponent("Transform").lock());
	Transform->SetLocalPos(mScene.lock()->GetCamera()->GetSizeView().x, mScene.lock()->GetCamera()->GetSizeView().y);

	// Animation
	CreateComponent<CAnimationComponent>("Animation");
	auto Animation = std::dynamic_pointer_cast<CAnimationComponent>(FindComponent("Animation").lock());
	
	Animation->SetTexture("PauseScreen");
	Animation->SetOpacity(0, 1.f);
	Animation->SetSortingOrder(50);

	Animation->AddAnimation("BackGround", "BackGround",FVector2D(0,0), FVector2D(256, 192.f), FVector2D(0.f,0.f), 1, 1);
	Animation->ChangeState("BackGround", 0);
	
	Animation->SetPlayOption(FAnimationPlayOption::Once);
	Animation->SetSpeed(0);

	//
	CreateChildObject<PausePrevNextPage>("Prev");
	std::dynamic_pointer_cast<CTransformComponent>(FindObject("Prev").lock()->FindComponent("Transform").lock())->SetLocalPos(-120.f, 0.f, 0.f);
	//
	CreateChildObject<PausePrevNextPage>("Next");
	std::dynamic_pointer_cast<CTransformComponent>(FindObject("Next").lock()->FindComponent("Transform").lock())->SetLocalPos(120.f, 0.f, 0.f);

	return true;
}

void PauseScreen::Update(float DeltaTime)
{
	CSceneObject::Update(CGameManager::GetInstance().GetDeltaTime());
}

void PauseScreen::PostUpdate(float DeltaTime)
{
	CSceneObject::PostUpdate(CGameManager::GetInstance().GetDeltaTime());

	if (IsMoving)
	{
		float CurScreenX = std::dynamic_pointer_cast<CTransformComponent>((FindObject(std::to_string(mCurScreen)).lock()->FindComponent("Transform").lock()))->GetLocalPosition().x;
		if ((MoveLeft && CurScreenX >= 0) || (MoveRight && CurScreenX <= 0))
		{
			// Cur는 내비두고, Prev와 Next를 삭제하고(숫자로 구분)
			for (auto o : mChildObjList)
			{
				if (o->GetName() == std::to_string(mCurScreen))
				{
					std::dynamic_pointer_cast<CTransformComponent>(o->FindComponent("Transform").lock())->SetVelocityX(0.f);
					std::dynamic_pointer_cast<CTransformComponent>(o->FindComponent("Transform").lock())->SetLocalPos(0.f, 0.f, 0.f);
					continue;
				}
				else if (!(strcmp(o->GetName(),"Prev") == 0 || strcmp(o->GetName(),"Next") == 0))
				{
					o->Destroy();
				}
			}
			IsCreateScreens = true;

			IsMoving = false;
			MoveLeft = false;
			MoveRight = false;
		}
	}
	else if (IsCreateScreens)
	{
		CreateScreens(FVector3D(-256.f, 0.f, 0.f), std::to_string(mPrevScreen));
		CreateScreens(FVector3D(256.f, 0.f, 0.f), std::to_string(mNextScreen));
		IsCreateScreens = false;
	}
}

void PauseScreen::InitScreenCount(int Count)
{
	mIndexCount = Count - 1;

	mPrevScreen = mIndexCount;
	mCurScreen = 0;
	mNextScreen = (1 % (mIndexCount + 1));

	CreateScreens(FVector3D(-256.f, 0.f, 0.f), std::to_string(mPrevScreen));
	CreateScreens(FVector3D(0.f, 0.f, 0.f), std::to_string(mCurScreen));
	CreateScreens(FVector3D(256.f, 0.f, 0.f), std::to_string(mNextScreen));
}

void PauseScreen::CreateScreens(FVector3D Position, std::string Name)
{
	CreateChildObject<PauseObject>(Name);
	std::dynamic_pointer_cast<CTransformComponent>(FindObject(Name).lock()->FindComponent("Transform").lock())->SetLocalPos(Position);
}

void PauseScreen::MoveScreenLeft(float DeltaTime)
{
	if (!IsMoving)
	{
		mCurScreen = mPrevScreen;
		mNextScreen = ((mCurScreen + 1) % (mIndexCount + 1));
		mPrevScreen = (mCurScreen - 1);
		if (mPrevScreen < 0) mPrevScreen = mIndexCount;

		for (auto o : mChildObjList)
		{
			if (!(strcmp(o->GetName(),"Prev") == 0 || strcmp(o->GetName(),"Next") == 0))
				std::dynamic_pointer_cast<CTransformComponent>(o->FindComponent("Transform").lock())->SetVelocityX(500.f);
		}

		IsMoving = true;
		MoveLeft = true;
	}
}

void PauseScreen::MoveScreenRight(float DeltaTime)
{
	if (!IsMoving)
	{
		mCurScreen = mNextScreen;
		mNextScreen = ((mCurScreen + 1) % (mIndexCount + 1));
		mPrevScreen = (mCurScreen - 1);
		if (mPrevScreen < 0) mPrevScreen = mIndexCount;

		for (auto o : mChildObjList)
		{
			auto a = strcmp(o->GetName(),"Prev");
			auto b = strcmp(o->GetName(),"Next");

			if (!(strcmp(o->GetName(),"Prev") == 0 || strcmp(o->GetName(),"Next") == 0))
				std::dynamic_pointer_cast<CTransformComponent>(o->FindComponent("Transform").lock())->SetVelocityX(-500.f);
		}

		IsMoving = true;
		MoveRight = true;
	}
}
