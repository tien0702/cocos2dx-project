#ifndef __ENEMY_STATE_FACTORY_H__
#define __ENEMY_STATE_FACTORY_H__


#include "Enemy/State/EnemyIdleState.h"
#include "Enemy/State/EnemyMoveState.h"
#include "Enemy/State/EnemyChasingState.h"
#include "Enemy/State/EnemyAttackState.h"
#include "Enemy/State/EnemySpawnState.h"
#include "Enemy/State/EnemyDieState.h"
#include "Enemy/State/EnemyTakeHitState.h"

namespace MyGame
{
	class EnemyStateFactory
	{
	public:
		static EnemyState* getEnemyStateByName(std::string name);
	};
}

#endif // !__ENEMY_STATE_FACTORY_H__
