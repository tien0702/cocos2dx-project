#include "CharacterDieState.h"
#include "Character/Character.h"
#include "Bitmask.h"
#include "ObjectTag.h"

void MyGame::CharacterDieState::enter(Character* owner)
{
	_elapsedTime = 0.0f;
	_owner = owner;
	_owner->setTag(ObjectTag::Other);
	this->initAnimation();

	Animation* ani = AnimationCache::getInstance()->getAnimation(_owner->getSpriteFileName() + "-" + "die");
	_time = ani->getFrames().size() * ani->getDelayPerUnit();

	PhysicsBody* body = _owner->getPhysicsBody();
	body->setEnabled(false);
}

std::string MyGame::CharacterDieState::updateState(float dt)
{
	_elapsedTime += dt;
	if (_elapsedTime > _time) return "";
	return "die";
}

void MyGame::CharacterDieState::exit()
{
	//_owner->unscheduleUpdate();
	//_owner->getParent()->removeChild(_owner, false);
}

bool MyGame::CharacterDieState::initAnimation()
{
	std::string spriteFileName = _owner->getSpriteFileName() + "-" + "die";
	Animation* animation = AnimationCache::getInstance()->getAnimation(spriteFileName);
	_owner->setAnimation(animation);
	return true;
}
