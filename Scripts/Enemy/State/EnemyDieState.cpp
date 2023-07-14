#include "EnemyDieState.h"
#include "Enemy/Enemy.h"
#include "ObjectTag.h"
#include "Enemy/EnemyPool.h"

void MyGame::EnemyDieState::enter(Enemy* enemy)
{
	_owner = enemy;
	_owner->setTag(ObjectTag::Other);
	_owner->getPhysicsBody()->setEnabled(false);
	_owner->enableRangeVisual(false);

	// Set animation
	std::string spriteFileName = _owner->getSpriteFileName() + "-" + "die";
	Animation* animation = AnimationCache::getInstance()->getAnimation(spriteFileName);
	_time = animation->getDelayPerUnit() * (animation->getFrames().size() * 1.0f);
	_owner->setAnimation(animation);
}

std::string MyGame::EnemyDieState::updateState(float dt)
{
	_time -= dt;
	if (_time > 0) return "die";
	_owner->getSprite()->stopActionByTag(Enemy::AnimationTag);
	_owner->removeFromParent();
	EnemyPool::getIns()->push(_owner);
	return "";
}

void MyGame::EnemyDieState::exit()
{
	_owner->setTag(ObjectTag::Enemy);
	_owner->getPhysicsBody()->setEnabled(true);
}
