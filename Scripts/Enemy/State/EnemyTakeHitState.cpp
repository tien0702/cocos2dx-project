#include "EnemyTakeHitState.h"
#include "Enemy/Enemy.h"
#include "Entity/BaseStat.h"
#include "AudioManager/AudioManager.h"

void MyGame::EnemyTakeHitState::enter(Enemy* enemy)
{
	_owner = enemy;
	// Set animation
	std::string spriteFileName = _owner->getSpriteFileName() + "-" + "take-hit";
	Animation* animation = AnimationCache::getInstance()->getAnimation(spriteFileName)->clone();
	_owner->setAnimation(animation);
	_elapsedTime = 0.0f;
	_duration = animation->getDelayPerUnit() * animation->getFrames().size();
}

std::string MyGame::EnemyTakeHitState::updateState(float dt)
{
	_elapsedTime += dt;
	if (_elapsedTime < _duration) return "take-hit";
	return "idle";
}

void MyGame::EnemyTakeHitState::exit()
{

}
