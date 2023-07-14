#ifndef __ENEMY_POOL_H__
#define __ENEMY_POOL_H__

#include "Enemy.h"

namespace MyGame
{
	class EnemyPool
	{
	public:
		static EnemyPool* getIns();
		void initEnemyByName(std::string name);
		Enemy* getEnemyByName(std::string name);
		int getMaxEnemy() { return _maxEnemy; }
		void push(Enemy* object);
		bool isExists(std::string name);
	private:
		EnemyPool();
		static EnemyPool* _instance;
		std::map<std::string, std::queue<Enemy*>>* _enemies;
		int _maxEnemy = 20;
	};
}

#endif // !__ENEMY_POOL_H__
