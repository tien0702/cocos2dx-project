#ifndef __I_PROJECTILE_H__
#define __I_PROJECTILE_H__

#include "cocos2d.h"
#include "DamagerSystem/Power.h"

USING_NS_CC;

namespace MyGame
{
	class BaseStat;
	class IProjectile
	{
	public:
		static const int AniTag = 1;
	public:
		virtual void triggered(Vec2 direction, Vec2 pos) = 0;
		virtual void destroy() = 0;
	protected:
		CC_SYNTHESIZE(int, _idType, IDType);
		CC_SYNTHESIZE(float, _range, Range);
		CC_SYNTHESIZE(float, _speed, ProjectileSpeed);
		CC_SYNTHESIZE(float, _radius, ProjectileRadius);
		CC_SYNTHESIZE(Power, _power, ProjectilePower);
		CC_SYNTHESIZE(std::string, _aniPath, AnimationPath);
		CC_SYNTHESIZE(std::string, _spriteFileName, ProjectilePath);

		CC_SYNTHESIZE(Vec2, _originPos, OriginPos);
		CC_SYNTHESIZE(Animation*, _destroyAni, AnimationDestroy);
	};
}

#endif // !__I_PROJECTILE_H__
