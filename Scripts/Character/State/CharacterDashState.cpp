#include "CharacterDashState.h"
#include "Character/Character.h"
#include "Input/PlayerInput.h"
#include "Input/Input.h"
#include "Entity/BaseStat.h"
#include "Manager/GameManager.h"
#include "Common.h"
#include "AudioManager/AudioManager.h"

void MyGame::CharacterDashState::enter(Character* owner)
{
	this->_owner = owner;
	_owner->getAbilityEquiplocation(ActiveSkillLocation::DashSkill)->use();
	this->loadProperties();
	this->initAnimation();
	this->dash();
	this->handleMove();
	AudioManager::getIns()->playEffect("Audio/huiya.mp3");
}

std::string MyGame::CharacterDashState::updateState(float dt)
{
	_elapsedTime += dt;

	this->handleMove();

	if (_elapsedTime > _castingTime) return "idle";

	return "dash";
}

void MyGame::CharacterDashState::exit()
{
	_owner->getPhysicsBody()->setVelocity(Vec2::ZERO);
}

bool MyGame::CharacterDashState::initAnimation()
{
	std::string spriteFileName = _owner->getSpriteFileName() + "-" + "evade";
	Animation* animation = AnimationCache::getInstance()->getAnimation(spriteFileName);

	float delay = _castingTime / (animation->getFrames().size() * 1.0f);
	animation->setDelayPerUnit(delay);
	_owner->setAnimation(animation);
	return true;
}

bool MyGame::CharacterDashState::loadProperties()
{
	_elapsedTime = 0.0f;
	_ability = _owner->getAbilityEquiplocation(ActiveSkillLocation::DashSkill);
	_dashSpeed = _ability->getStatByID(Stat::MoveSpeed);
	_map = GameManager::getIns()->getCurrentMap();

	auto castingTime = _ability->getStatByID(Stat::CastingTime);
	auto powerRate = _ability->getStatByID(Stat::PowerRate);
	_castingTime = castingTime->getFinalValue() * 0.001f;
	_castingTime *= (powerRate->getFinalValue() * 0.01f);
	//_castingTime *= CONVERT_TO_PERCENT(powerRate->getFinalValue());

	return true;
}

void MyGame::CharacterDashState::dash()
{
	// 
	Vec2 direction = Input::getIns()->getDirection(true);
	if (direction == Vec2::ZERO)
	{
		bool isFlipX = _owner->getSprite()->isFlippedX();
		direction.x = (isFlipX) ? (1) : (-1);
	}
	float speed = _dashSpeed->getFinalValue() * 1.0f;

	Vec2 velocity = direction * speed;
	PhysicsBody* body = _owner->getPhysicsBody();
	body->setVelocity(velocity);
	if (direction.x != 0)
		_owner->getSprite()->setFlippedX(direction.x > 0);
}

Vec2 MyGame::CharacterDashState::calculateNextPos(float time)
{
	Vec2 curPos = getGroundPosOwner();
	Vec2 offsetPos = _owner->getPhysicsBody()->getVelocity() * time;

	return (curPos + offsetPos);
}

Vec2 MyGame::CharacterDashState::getGroundPosOwner() const
{
	return Vec2(_owner->getPosition().x,
		_owner->getPosition().y - (_owner->getEntitySize().height / 2.0f));
}

void MyGame::CharacterDashState::handleMoveMeta(int metaType, Vec2 vel)
{
	switch (metaType)
	{
	case MetaType::insideRed:
		_owner->getPhysicsBody()->setVelocity(Vec2::ZERO);
		break;
	case MetaType::insideGreen:
		_owner->getPhysicsBody()->setVelocity(vel);
		break;
	default:
		_owner->getPhysicsBody()->setVelocity(vel);
		break;
	}
}

void MyGame::CharacterDashState::handleMove()
{
	Vec2 nextPos = this->calculateNextPos(0.02f);
	int metaType = _map->getMetaAtPos(nextPos);
	this->handleMoveMeta(metaType, _owner->getPhysicsBody()->getVelocity());
}
