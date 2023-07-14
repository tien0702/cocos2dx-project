#ifndef __ENEMY_IDLE_STATE_H__
#define __ENEMY_IDLE_STATE_H__

#include "Enemy/State/EnemyState.h"

namespace MyGame
{
	class BaseStat;
	class EnemyIdleState : public EnemyState
	{
	public:
		virtual void enter(Enemy* enemy);
		virtual std::string updateState(float dt);
		virtual void exit();
	private:
		float _elapsedTime = 0.0f;
		Node* _target;
		BaseStat* _rangeFind;
		BaseStat* _breakTime;

	private:
		bool checkChasing();
	};
}

#endif // !__ENEMY_IDLE_STATE_H__
