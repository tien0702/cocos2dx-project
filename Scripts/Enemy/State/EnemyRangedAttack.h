#ifndef __ENEMY_RANGED_ATTACK_H__
#define __ENEMY_RANGED_ATTACK_H__

#include "Enemy/State/EnemyState.h"

namespace MyGame
{
	class BaseStat;
	class EnemyRangedAttack : public EnemyState
	{
	public:
		virtual void enter(Enemy* enemy);
		virtual std::string updateState(float dt);
		virtual void exit();
	private:
		float _elapsedTime;
		float _activationTime;
	};
}

#endif // !__ENEMY_RANGED_ATTACK_H__
