#ifndef __DASH_ACTIVATION_H__
#define __DASH_ACTIVATION_H__

#include "ActivationStrategy.h"

namespace MyGame
{
	class DashActivation : public SkillActivation
	{
	public:
		void activate(Skill* skill, Vec2 position, float rotation, Vec2 direction) override;
	private:
	};
}

#endif // !__DASH_ACTIVATION_H__
