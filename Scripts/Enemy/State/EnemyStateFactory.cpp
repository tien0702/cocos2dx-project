#include "EnemyStateFactory.h"

MyGame::EnemyState* MyGame::EnemyStateFactory::getEnemyStateByName(std::string name)
{
	EnemyState* state = nullptr;

	if (name == "spawn")
	{
		state = new EnemySpawnState();
	}
	else if (name == "idle")
	{
		state = new EnemyIdleState();
	}
	else if (name == "move")
	{
		state = new EnemyMoveState();
	}
	else if (name == "chasing")
	{
		state = new EnemyChasingState();
	}
	else if (name == "attack")
	{
		state = new EnemyAttackState();
	}
	else if (name == "die")
	{
		state = new EnemyDieState();
	}
	else if (name == "take-hit")
	{
		state = new EnemyTakeHitState();
	}
	return state;
}
