#include "ProfileManager.h"

bool CProfileManager::Init()
{
	CreateProfile("Default", ECollisionChannel::Default, true, ECollisionInteraction::Collision);
	CreateProfile("Player", ECollisionChannel::Player, true, ECollisionInteraction::Collision);
	CreateProfile("Monster", ECollisionChannel::Monster, true, ECollisionInteraction::Collision);
	CreateProfile("PlayerAttack", ECollisionChannel::PlayerAttack, true, ECollisionInteraction::Collision);
	CreateProfile("MonsterAttack", ECollisionChannel::MonsterAttack, true, ECollisionInteraction::Collision);

	// 세팅..

	SetInteraction("Player", ECollisionChannel::Player, ECollisionInteraction::Ignore);
	SetInteraction("PlayerAttack", ECollisionChannel::Player, ECollisionInteraction::Ignore);

	return true;
}

bool CProfileManager::CreateProfile(const std::string& Name,ECollisionChannel::Type Channel,bool Enable,ECollisionInteraction::Type Interaction)
{
	std::shared_ptr<FCollisionProfile> Profile = FindProfile(Name);

	if (Profile != nullptr)
	{
		return false;
	}

	Profile = std::make_shared<FCollisionProfile>();

	Profile->Name = Name;
	Profile->Channel = Channel;
	Profile->Enable = Enable;

	for (int i = 0; i < ECollisionChannel::End; ++i)
	{
		Profile->Interaction[i] = Interaction;
	}

	mProfileMap.insert(std::make_pair(Name, Profile));

	return true;
}

bool CProfileManager::SetInteraction(const std::string & Name,ECollisionChannel::Type Channel,ECollisionInteraction::Type Interaction)
{
	std::shared_ptr<FCollisionProfile> Profile = FindProfile(Name);

	if (Profile != nullptr)
	{
		return false;
	}

	Profile->Interaction[Channel] = Interaction;

	return true;
}

bool CProfileManager::SetEnable(const std::string& Name, bool Enable)
{
	std::shared_ptr<FCollisionProfile> Profile = FindProfile(Name);

	if (Profile != nullptr)
	{
		return false;
	}

	Profile->Enable = Enable;

	return true;
}

std::shared_ptr<FCollisionProfile> CProfileManager::FindProfile(const std::string & Name)
{
	auto iter = mProfileMap.find(Name);

	if (iter == mProfileMap.end())
	{
		return nullptr;
	}

	return iter->second;
}

CProfileManager::CProfileManager()
{
}

CProfileManager::~CProfileManager()
{
}
