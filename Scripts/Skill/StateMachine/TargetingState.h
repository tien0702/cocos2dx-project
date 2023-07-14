#ifndef __TARGETING_STATE_H__
#define __TARGETING_STATE_H__

#include "SkillState.h"

namespace MyGame
{
	class TargetingState : public SkillState
	{
	public:
		virtual void enter(Skill* skill);
		virtual SkillStateType excute(float dt);
		virtual void exit();
	private:
	};
}

#endif // !__TARGETING_STATE_H__
