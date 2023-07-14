#ifndef __A0E_DELAY_ACTIVATION_H__
#define __A0E_DELAY_ACTIVATION_H__

#include "ActivationStrategy.h"


namespace MyGame
{
	class AoEDelayActivation : public SkillActivation
	{
	public:
		void activate(Skill* skill, Vec2 position, float rotation, Vec2 direction) override;
	private:
		void dealDamage();
		std::list<Node*>* getEnemiesInArea();
		void playAnimation(Vec2 position);
	};
}

#endif // !__A0E_DELAY_ACTIVATION_H__
