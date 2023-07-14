#include "CharacterSpawnState.h"
#include "Character/Character.h"
#include "Character/State/CharacterStateMachine.h"
#include "Bitmask.h"
#include "ObjectTag.h"

void MyGame::CharacterSpawnState::enter(Character* owner)
{
	_owner = owner;
	_owner->getHealth()->reborn();
	_owner->setTag(ObjectTag::Player);
	auto children = _owner->getChildren();
	/*_owner->scheduleUpdate();
	for (auto child : children)
	{
		child->scheduleUpdate();
	}*/
	PhysicsBody* body = _owner->getPhysicsBody();
	body->setEnabled(true);
	setup();

	_elapsedTime = 0.0f;
	this->initAnimation();
}

std::string MyGame::CharacterSpawnState::updateState(float dt)
{
	_elapsedTime += dt;
	if (_elapsedTime > _spawnTime) return "idle";
	return "spawn";
}

void MyGame::CharacterSpawnState::exit()
{
}

MyGame::CharacterSpawnState::CharacterSpawnState()
{
}

bool MyGame::CharacterSpawnState::initAnimation()
{
	std::string spriteFileName = _owner->getSpriteFileName() + "-" + "spawn";
	Animation* animation = AnimationCache::getInstance()->getAnimation(spriteFileName);
	_spawnTime = animation->getDuration();
	_owner->setAnimation(animation);
	return true;
}

void MyGame::CharacterSpawnState::setup()
{
}
