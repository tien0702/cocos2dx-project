#include "EnemyRangedAttack.h"
#include "Enemy/Enemy.h"
#include "Entity/DetectEntity.h"
#include "Bitmask.h"
#include "ObjectTag.h"

void MyGame::EnemyRangedAttack::enter(Enemy* enemy)
{
	_owner = enemy;
	_elapsedTime = 0.0f;
	// Set animation
	std::string spriteFileName = _owner->getSpriteFileName() + "-" + "attack";
	Animation* animation = AnimationCache::getInstance()->getAnimation(spriteFileName)->clone();
	float atkSpeed = 1000.0f / (_owner->getEntityStatByID(Stat::ATKSpeed)->getFinalValue() * 1.0f);
	float timeAni = atkSpeed / (animation->getFrames().size() * 1.0f);
	animation->setDelayPerUnit(timeAni);
	_owner->setAnimation(animation);
}

std::string MyGame::EnemyRangedAttack::updateState(float dt)
{
	_elapsedTime += dt;
	return "ranged-attack";
}

void MyGame::EnemyRangedAttack::exit()
{
}
