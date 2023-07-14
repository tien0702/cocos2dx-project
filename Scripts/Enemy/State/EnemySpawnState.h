#ifndef __ENEMY_SPAWN_STATE_H__
#define __ENEMY_SPAWN_STATE_H__

#include "Enemy/State/EnemyState.h"

namespace MyGame
{
	class EnemySpawnState : public EnemyState
	{
	public:
		virtual void enter(Enemy* enemy);
		virtual std::string updateState(float dt);
		virtual void exit();
	private:
		float _timeSpawn;
	};
}

#endif // !__ENEMY_SPAWN_STATE_H__
