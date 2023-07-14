#ifndef __ENEMY_CHASING_STATE_H__
#define __ENEMY_CHASING_STATE_H__

#include "Enemy/State/EnemyState.h"

namespace MyGame
{
	class BaseStat;
	class EnemyChasingState : public EnemyState
	{
	public:
		virtual void enter(Enemy* enemy);
		virtual std::string updateState(float dt);
		virtual void exit();
		EnemyChasingState();
	private:
		float _elapsedTime;
		float _timeReCheck;
	private:
		Vec2 getVelocity();
		bool targetIsOutside();
		bool checkTargetState();
		void updateFlipX();
		bool canAttack();

		BaseStat* _runSpeed;
		Sprite* _chasingWarning;
		Node* _target;
	};
}

#endif // !__ENEMY_CHASING_STATE_H__
