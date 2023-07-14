#include "EnemyChasingState.h"
#include "Enemy/Enemy.h"
#include "Entity/DetectEntity.h"
#include "ObjectTag.h"

void MyGame::EnemyChasingState::enter(Enemy* enemy)
{
	_owner = enemy;
	_timeReCheck = 0.75f;
	_elapsedTime = 0.0f;

	_runSpeed = _owner->getEntityStatByID(Stat::RunSpeed);

	_target = DetectEntity::findCharacter();
	_owner->getPhysicsBody()->setVelocity(this->getVelocity());
	this->updateFlipX();

	//
	Vec2 posChasingWarning;
	posChasingWarning.x = 0;
	posChasingWarning.y = _owner->getSprite()->getContentSize().height / 2 + 10;
	_chasingWarning->setPosition(posChasingWarning);
	_owner->addChild(_chasingWarning);

	// Set animation
	std::string spriteFileName = _owner->getSpriteFileName() + "-" + "move";
	Animation* animation = AnimationCache::getInstance()->getAnimation(spriteFileName);
	_owner->setAnimation(animation);
}

std::string MyGame::EnemyChasingState::updateState(float dt)
{
	_elapsedTime += dt;
	if (this->targetIsOutside()) return "idle";

	// Check chasing
	if (_elapsedTime < _timeReCheck)
	{
		return "chasing";
	}
	else
	{
		_elapsedTime = 0.0f;
	}

	if (this->canAttack()) return "attack";
	// 
	BaseStat* rangeFind = _owner->getEntityStatByID(Stat::RangeFind);
	float rangeFindVal = rangeFind->getFinalValue();
	if (_owner->getPosition().distance(_target->getPosition()) < rangeFindVal)
	{
		_owner->getPhysicsBody()->setVelocity(this->getVelocity());
		this->updateFlipX();
		return "chasing";
	}

	return "idle";
}

void MyGame::EnemyChasingState::exit()
{
	_owner->getPhysicsBody()->setVelocity(Vec2::ZERO);
	_chasingWarning->removeFromParent();
}

MyGame::EnemyChasingState::EnemyChasingState()
{
	_chasingWarning = Sprite::create("FHD/Icon/chasing-warning.png");
	_chasingWarning->retain();
}

Vec2 MyGame::EnemyChasingState::getVelocity()
{
	// Chasing
	Vec2 dir = _target->getPosition() - _owner->getPosition();
	dir.normalize();
	return dir * _runSpeed->getFinalValue();
}

bool MyGame::EnemyChasingState::targetIsOutside()
{
	Vec2 posChar = _target->getPosition();
	return !_owner->getEnemySpawnArea().containsPoint(posChar);
}

bool MyGame::EnemyChasingState::checkTargetState()
{
	if (_target == nullptr) return false;
	if (_target->getTag() != ObjectTag::Player) return false;

	return true;
}

void MyGame::EnemyChasingState::updateFlipX()
{
	Vec2 dir = _target->getPosition() - _owner->getPosition();
	_owner->getSprite()->setFlippedX(dir.x < 0);
}

bool MyGame::EnemyChasingState::canAttack()
{
	if (!checkTargetState()) return false;

	BaseStat* rangeAttack = _owner->getEntityStatByID(Stat::RangeAttack);
	float rangeAttackVal = rangeAttack->getFinalValue();
	return (_target->getPosition().distance(_owner->getPosition()) < rangeAttackVal);
}
