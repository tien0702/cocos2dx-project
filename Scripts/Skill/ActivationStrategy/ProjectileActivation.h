#ifndef __PROJECTILE_ACTIVATION_H__
#define __PROJECTILE_ACTIVATION_H__

#include "Skill/ActivationStrategy/ActivationStrategy.h"

namespace MyGame
{
	class ProjectileActivation : public SkillActivation
	{
	public:
		void activate(Skill* skill, Vec2 position, float rotation, Vec2 direction) override;

	private:
		void shootOut(Vec2 direction);
		void preExplosive();
		void explosive();

		void playAnimationShootOut();
		void playAnimationExplosive();
		void update(float dt);
		void dealDamage();
		void setupForProjectile(Vec2 position, float rotation);
		void autoExit();
		void exit();

		bool loadProjectile();
		bool initBody();
		bool onContactBegin(PhysicsContact& contact);

		bool isOutRange();
		bool insideMetaAllow();
	private:
		Vec2 _originPos;
		int TagAnimation = 1;
		Sprite* _projectileVisual;
		bool _isLoaded = false;
		bool _isExplosive = false;
		float _timeOut;
	};
}

#endif // !__PROJECTILE_ACTIVATION_H__
