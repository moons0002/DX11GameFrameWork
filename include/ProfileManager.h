#pragma once

#include "GameInfo.h"

namespace ECollisionChannel
{
	enum Type : unsigned char
	{
		Default,
		Player,
		Monster,
		PlayerAttack,
		MonsterAttack,
		End
	};
}

namespace ECollisionInteraction
{
	enum Type : unsigned char
	{
		Ignore,
		Collision,
		End
	};
}

struct FCollisionProfile
{
	std::string Name;
	ECollisionChannel::Type Channel = ECollisionChannel::Default;
	bool Enable = true;
	ECollisionInteraction::Type Interaction[ECollisionChannel::End];
};

class CProfileManager
{
private:
	std::unordered_map<std::string, std::shared_ptr<FCollisionProfile>> mProfileMap;

public:
	bool Init();

	bool CreateProfile(const std::string& Name, ECollisionChannel::Type Channel, bool Enable, ECollisionInteraction::Type Interaction);
	
	bool SetInteraction(const std::string& Name, ECollisionChannel::Type Channel, ECollisionInteraction::Type Interaction);

	bool SetEnable(const std::string& Name, bool Enable);

	std::shared_ptr<FCollisionProfile> FindProfile(const std::string& Name);

private:
	CProfileManager();
	~CProfileManager();
	CProfileManager(const CProfileManager&) = delete;
	void operator=(const CProfileManager&) = delete;

public:
	static CProfileManager &GetInstance() {
		static CProfileManager inst;
		return inst;
	}
};

