#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "Projectile/IProjectile.h"

namespace MyGame
{
	class Entity;
	class Projectile : public IProjectile, public Sprite
	{
	public:
		virtual bool init();
		virtual void triggered(Vec2 direction, Vec2 pos);
		virtual void destroy();
	protected:
		CC_SYNTHESIZE(Entity*, _owner, Owner);
		Sprite* _visual;
		Animation* _objAni, * _objDestroy;
	protected:
		virtual bool onContactBegin(const PhysicsContact& contact);
		virtual void update(float dt);
		virtual void fixedUpdate(float dt);

		virtual bool canMoveOnMeta();
		virtual bool inRange();
	};
}

#endif // !__PROJECTILE_H__
