#ifndef __SKILL_H__
#define __SKILL_H__

#include "cocos2d.h"
#include "Skill/SkillInfo.h"
#include "DamagerSystem/Power.h"
#include "Input/PlayerInput.h"
#include "TargetingStrategy/TargetingStrategy.h"
#include "ActivationStrategy/ActivationStrategy.h"

USING_NS_CC;

namespace MyGame
{
	class Entity;
	class BaseStat;
	class SkillStateMachine;
	class Skill : public Sprite
	{
	public:
		bool init();
		BaseStat* getStatByID(int id);
		void setStats(std::map<int, BaseStat*> stats) { _stats = stats; }
	private:
		CC_SYNTHESIZE(SkillInfo*, _info, Info);
		CC_SYNTHESIZE(Entity*, _onwer, Owner);
		CC_SYNTHESIZE(Power*, _power, SkillPower);
		CC_SYNTHESIZE(InputID, _activationButtonID, ActivationButtonID);

		// effect
		std::map<int, BaseStat*> _stats;
		CC_SYNTHESIZE(SkillStateMachine*, _stateMachine, StateMachine);
		CC_SYNTHESIZE(SkillTargeting*, _targeting, Targeting);
		CC_SYNTHESIZE(SkillActivation*, _activation, Activation);
	private:
		bool loadAnimation();
	};
}

#endif // !__SKILL_H__
