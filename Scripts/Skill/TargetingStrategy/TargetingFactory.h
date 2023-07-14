#ifndef __TARGETING_FACTORY_H__
#define __TARGETING_FACTORY_H__

#include "TargetingStrategy.h"

namespace MyGame
{
	enum class TargetingType
	{
		AreaAroundSelf,
		Projectile,
		SelectArea,
		TargetSelf,
		SelectEnemy
	};
	class TargetingFactory
	{
	public:
		static SkillTargeting* getTargetingByType(TargetingType type);

	};
}

#endif // !__TARGETING_FACTORY_H__
