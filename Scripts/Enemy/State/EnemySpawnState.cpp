#include "EnemySpawnState.h"
#include "Enemy/Enemy.h"
#include "ObjectTag.h"

void MyGame::EnemySpawnState::enter(Enemy* enemy)
{
	_owner = enemy;
	_owner->setTag(ObjectTag::Other);
	_owner->getPhysicsBody()->setEnabled(false);

	// Set animation
	std::string spriteFileName = _owner->getSpriteFileName() + "-" + "spawn";
	Animation* animation = AnimationCache::getInstance()->getAnimation(spriteFileName)->clone();
	_timeSpawn = animation->getDelayPerUnit() * (animation->getFrames().size() * 1.0f);
	_owner->setAnimation(animation);
}

std::string MyGame::EnemySpawnState::updateState(float dt)
{
	_timeSpawn -= dt;
	if (_timeSpawn > 0.0f) return "spawn";
	_owner->getPhysicsBody()->setEnabled(true);
	_owner->setTag(ObjectTag::Enemy);
	return "idle";
}

void MyGame::EnemySpawnState::exit()
{
	//_owner->enableRangeVisual(true);
}
