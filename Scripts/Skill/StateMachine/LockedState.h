#ifndef __LOCKED_STATE_H__
#define __LOCKED_STATE_H__

#include "SkillState.h"

namespace MyGame
{
	class LockedState : public SkillState
	{
	public:
		virtual void enter(Skill* skill);
		virtual SkillStateType excute(float dt);
		virtual void exit();
	private:
		bool isEnoughMana();
		bool isPressActivationButton();
		void updateUIButtonWithState(bool isLocked);
	};
}

#endif // !__LOCKED_STATE_H__
