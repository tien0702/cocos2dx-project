#ifndef __SKILL_STATE_TYPE_H__
#define __SKILL_STATE_TYPE_H__

namespace MyGame
{
	enum class SkillStateType
	{
		Ready,
		Targeting,
		Casting,
		Cooldown,
		Locked
	};
}

#endif // !__SKILL_STATE_TYPE_H__
