#ifndef __AOE_ACTIVATION_H__
#define __AOE_ACTIVATION_H__

#include "ActivationStrategy.h"

namespace MyGame
{
	class AoEActivation : public SkillActivation
	{
	public:
		void activate(Skill* skill, Vec2 position, float rotation, Vec2 direction) override;
	private:
		void update(float dt);
		void setupForAoE(Vec2 position);
		void playAnimation();
		void dealDamage();
		void autoExit();
		void exit();
		bool loadProperties();

		float getBootTime();
		void start();
	private:
		Sprite* _skillVisual;
		bool _isLoaded;
	};
}

#endif // !__AOE_ACTIVATION_H__
