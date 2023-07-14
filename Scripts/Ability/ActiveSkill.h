#ifndef __I_ABILITY_H__
#define __I_ABILITY_H__

#include "cocos2d.h"
#include "Character/CharacterObserver.h"
#include "DamagerSystem/Power.h"

USING_NS_CC;

namespace MyGame
{
	class BaseStat;
	class Entity;

	enum class ActiveSkillLocation
	{
		UltimateSkill,
		TalenSkill,
		DashSkill,
		NormalAttackSkill,
		Non
	};

	class ActiveSkill : public Node
	{
	public:
		virtual bool init();
		ActiveSkill();
	public:
		virtual bool use();
		virtual bool canUse();
		virtual bool isReady();

		virtual void addStat(BaseStat* newStat);
		virtual void removeStat(int statID);
		virtual void setStats(std::map<int, BaseStat*>* abilityStats);
		virtual BaseStat* getStatByID(int id);
	protected:
		float _elapsedTime;

		bool _canUse;
	protected:
		bool statExists(int id);

		virtual void update(float dt);
		virtual void completedCooldown();
		virtual void cooldownStart();
	protected:
		CC_SYNTHESIZE(int, _id, ID);
		CC_SYNTHESIZE(int, _level, Level);
		CC_SYNTHESIZE(int, _unlockLevel, UnlockLevel);
		CC_SYNTHESIZE(int, _stack, CurrentStack);
		CC_SYNTHESIZE(float, _cooldown, Cooldown);
		CC_SYNTHESIZE(ActiveSkillLocation, _location, EquipLocation);
		CC_SYNTHESIZE(std::string, _abilityName, AbilityName);
		CC_SYNTHESIZE(std::string, _description, Description);
		CC_SYNTHESIZE(std::string, _iconPath, IconPath);

		CC_SYNTHESIZE(Power*, _power, SkillPower);
		CC_SYNTHESIZE(std::list<int>, _stateAlloweds, StateAlloweds);
		CC_SYNTHESIZE(Entity*, _owner, Owner);
		std::map<int, BaseStat*>* _abilityStats;
	};
}

#endif // !__I_ABILITY_H__
