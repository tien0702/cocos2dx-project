#ifndef __SKILL_EFFECT_H__
#define __SKILL_EFFECT_H__

#include "cocos2d.h"

USING_NS_CC;

namespace MyGame
{
	class Entity;
	class Skill;
	class SkillEffect
	{
	public:
		virtual void apply(Skill* owner, Entity* target) = 0;
	};
}


#endif // !__SKILL_EFFECT_H__
