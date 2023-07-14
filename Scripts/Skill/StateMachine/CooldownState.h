#ifndef __COOLDOWN_STATE_H__
#define __COOLDOWN_STATE_H__

#include "SkillState.h"

namespace MyGame
{
	class BaseStat;
	class CooldownState : public SkillState
	{
	public:
		virtual void enter(Skill* skill);
		virtual SkillStateType excute(float dt);
		virtual void exit();
	private:
		float _remainingCooldown = 0.0f;
		BaseStat* _cooldown;
	private:
		float getCooldown();
	};
}

#endif // !__COOLDOWN_STATE_H__
