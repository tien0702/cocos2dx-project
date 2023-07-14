#ifndef __ACTIVATION_STRATEGY_H__
#define __ACTIVATION_STRATEGY_H__


#include "cocos2d.h"

USING_NS_CC;

namespace MyGame
{
	class Skill;
	class SkillActivation : public Node
	{
	public:
		virtual void activate(Skill* skill, Vec2 position, float rotation, Vec2 direction) = 0;
		virtual void takeMana();
	protected:
		Skill* _skill;
	};
}

#endif // !__ACTIVATION_STRATEGY_H__
