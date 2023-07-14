#ifndef __PROJECTILE_POOL_H__
#define __PROJECTILE_POOL_H__
#include "Projectile/Projectile.h"

namespace MyGame
{
	class ProjectilePool
	{
	public:
		static ProjectilePool* getIns();
		Projectile* get(int id);
		int getMaxProjectile() { return _maxProjectile; }
		void push(Projectile* object);
		void destroyProjectile(int id);
	private:
		ProjectilePool();
	private:
		static ProjectilePool* _instance;
		int _maxProjectile = 100;
		std::map<int, std::queue<Projectile*>>* _projectiles;
	};
}

#endif // !__PROJECTILE_POOL_H__
