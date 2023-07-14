#ifndef __TARGETING_STRATEGY_H__
#define __TARGETING_STRATEGY_H__

#include "cocos2d.h"

USING_NS_CC;

namespace MyGame
{
	class Skill;
	class SkillTargeting
	{
	public:
		virtual void target(Skill* skill) = 0;
		virtual void activeSkill(Vec2 position) = 0;
	protected:
		virtual bool checkInput() const;
		Skill* _skill;
	};
}

#endif // !__TARGETING_STRATEGY_H__
