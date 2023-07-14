#include "EnemyTransitionState.h"
#include "Enemy/EnemyPool.h"

void MyGame::EnemyTransitionState::enter(Enemy* enemy)
{
	this->_owner = enemy;

}

std::string MyGame::EnemyTransitionState::updateState(float dt)
{
	return std::string();
}

void MyGame::EnemyTransitionState::exit()
{
}
