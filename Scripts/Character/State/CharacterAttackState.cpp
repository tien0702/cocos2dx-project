#include "CharacterAttackState.h"
#include "Character/Character.h"
#include "AudioManager/AudioManager.h"

void MyGame::CharacterAttackState::enter(Character* owner)
{
	this->_owner = owner;
	this->loadProperties();
	this->initAnimation();
	AudioManager::getIns()->playEffect("Audio/pew.mp3");
}

std::string MyGame::CharacterAttackState::updateState(float dt)
{
	_elapsedTime += dt;
	if (_elapsedTime > _castingTime) return "idle";
	return "attack";
}

void MyGame::CharacterAttackState::exit()
{
}

bool MyGame::CharacterAttackState::initAnimation()
{
	std::string spriteFileName = _owner->getSpriteFileName() + "-" + "attack";
	Animation* animation = AnimationCache::getInstance()->getAnimation(spriteFileName);
	float delay = _castingTime / (animation->getFrames().size() * 1.0f);
	animation->setDelayPerUnit(delay);
	_owner->setAnimation(animation);
	return true;
}

bool MyGame::CharacterAttackState::loadProperties()
{
	_attackSpeed = _owner->getEntityStatByID(Stat::ATKSpeed);
	_castingTime = 1000.0f / (_attackSpeed->getFinalValue() * 1.0f);
	
	_elapsedTime = 0.0f;
	return true;
}
