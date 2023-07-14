#ifndef __ENEMY_ATTACK_STATE_H__
#define __ENEMY_ATTACK_STATE_H__

#include "Enemy/State/EnemyState.h"

namespace MyGame
{
	class BaseStat;
	class EnemyAttackState : public EnemyState
	{
	public:
		virtual void enter(Enemy* enemy);
		virtual std::string updateState(float dt);
		virtual void exit();
		EnemyAttackState();
	private:
		float _elapsedTime;
		float _activationTime;
		std::vector<std::string> _randomStates;
		Node* _target;
		BaseStat* _rangeAttack;
		BaseStat* _attack;

		void attack();
		void updateFlipX();
		bool targetIsOutside();
		bool canAttack();
		std::string randomNextState();
	};
}

#endif // !__ENEMY_ATTACK_STATE_H__
