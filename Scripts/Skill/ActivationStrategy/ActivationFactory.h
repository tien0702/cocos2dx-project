#ifndef __ACTIVATION_FACTORY_H__
#define __ACTIVATION_FACTORY_H__

#include "ActivationStrategy.h"
#include "AoEActivation.h"
#include "ProjectileActivation.h"

namespace MyGame
{
	enum class ActivationType
	{
		AoEActi,
		ProjectileActi
	};

	class ActivationFactory
	{
	public:
		static SkillActivation* getActivationByType(ActivationType type);
	};
}

#endif // !__ACTIVATION_FACTORY_H__
