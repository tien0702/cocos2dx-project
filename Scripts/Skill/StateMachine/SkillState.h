#ifndef __SKILL_STATE_H__
#define __SKILL_STATE_H__

#include "SkillStateType.h"

namespace MyGame
{
	class Skill;
	class SkillState
	{
	public:
		virtual void enter(Skill* owner) = 0;
		virtual SkillStateType excute(float dt) = 0;
		virtual void exit() = 0;
	protected:
		Skill* _skill;
	};
}

#endif // !__SKILL_STATE_H__
