#ifndef __ENEMY_TAKE_HIT_STATE_H__
#define __ENEMY_TAKE_HIT_STATE_H__

#include "Enemy/State/EnemyState.h"

namespace MyGame
{
	class EnemyTakeHitState : public EnemyState
	{
	public:
		virtual void enter(Enemy* enemy);
		virtual std::string updateState(float dt);
		virtual void exit();
	private:
		float _elapsedTime;
		float _duration;
	};
}

#endif // !__ENEMY_TAKE_HIT_STATE_H__
