#ifndef __ENEMY_DIE_STATE_H__
#define __ENEMY_DIE_STATE_H__

#include "Enemy/State/EnemyState.h"

namespace MyGame
{
	class EnemyDieState : public EnemyState
	{
	public:
		virtual void enter(Enemy* enemy);
		virtual std::string updateState(float dt);
		virtual void exit();
	private:
		float _time;
	};
}

#endif // !__ENEMY_DIE_STATE_H__
