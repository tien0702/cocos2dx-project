#ifndef __READY_STATE_H__
#define __READY_STATE_H__

#include "SkillState.h"

namespace MyGame
{
	class ReadyState : public SkillState
	{
	public:
		virtual void enter(Skill* skill);
		virtual SkillStateType excute(float dt);
		virtual void exit();
	private:
		bool isEnoughMana();
		bool isPressActivationButton();
	};
}

#endif // !__READY_STATE_H__
