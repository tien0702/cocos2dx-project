#include "EnemyAttackState.h"
#include "Enemy/Enemy.h"
#include "Entity/DetectEntity.h"
#include "Bitmask.h"
#include "Common.h"
#include "ObjectTag.h"

void MyGame::EnemyAttackState::enter(Enemy* enemy)
{
	_owner = enemy;
	_elapsedTime = 0.0f;
	_attack = _owner->getEntityStatByID(Stat::ATK);
	_rangeAttack = _owner->getEntityStatByID(Stat::RangeAttack);

	_target = DetectEntity::findCharacter();
	if (_target != nullptr)
	{
		this->updateFlipX();
	}

	// Set animation
	std::string spriteFileName = _owner->getSpriteFileName() + "-" + "attack";
	Animation* animation = AnimationCache::getInstance()->getAnimation(spriteFileName)->clone();
	float atkSpeed = 1000.0f / (_owner->getEntityStatByID(Stat::ATKSpeed)->getFinalValue() * 1.0f);
	float timeAni = atkSpeed / (animation->getFrames().size() * 1.0f);
	animation->setDelayPerUnit(timeAni);
	_owner->setAnimation(animation);

	_activationTime = timeAni * 0.75f;
}

std::string MyGame::EnemyAttackState::updateState(float dt)
{
	_elapsedTime += dt;
	// Target is null
	if (_target == nullptr) return this->randomNextState();

	// Check attack speed
	float atkSpeed = 1000.0f / (_owner->getEntityStatByID(Stat::ATKSpeed)->getFinalValue() * 1.0f);
	if (_elapsedTime < atkSpeed) return "attack";

	// Check range target
	if (this->targetIsOutside()) return this->randomNextState();

	// Check casting time
	if (_elapsedTime < _activationTime) return "attack";
	
	// check target 
	if (!canAttack()) this->randomNextState();

	// repeat attack
	this->attack();
	this->updateFlipX();

	_elapsedTime = 0.0f;
	return "attack";
}

void MyGame::EnemyAttackState::exit()
{
}

MyGame::EnemyAttackState::EnemyAttackState()
{
	_randomStates.push_back("idle");
	_randomStates.push_back("move");
}

void MyGame::EnemyAttackState::attack()
{
	float distance = _target->getPosition().distance(_owner->getPosition());
	float rangeAttackVal = _rangeAttack->getFinalValue();
	if (distance > rangeAttackVal) return;

	// Attack to Character;
	Character* character = DetectEntity::getCharacter();
	if (character == nullptr)
	{
		log("Get character failed| EnemyAttackState");
		return;
	}

	Power power;
	power.setPowerValue(1.5f);
	power.setPowerNumber(0);
	power.setElemType(ElementType::PyroType);
	float critRate = CONVERT_TO_PERCENT(_owner->getEntityStatByID(Stat::CritRate)->getFinalValue());
	DamageMessage* dameData = DamageMessage::calculateDamage(_owner, character, power, critRate);

	character->takeDamage(dameData);
}

void MyGame::EnemyAttackState::updateFlipX()
{
	Vec2 dir = _target->getPosition() - _owner->getPosition();
	_owner->getSprite()->setFlippedX(dir.x < 0);
}

bool MyGame::EnemyAttackState::targetIsOutside()
{
	float distance = _target->getPosition().distance(_owner->getPosition());
	float rangeAttackVal = _rangeAttack->getFinalValue();
	return (distance > rangeAttackVal);
}

bool MyGame::EnemyAttackState::canAttack()
{
	if (_target == nullptr) return false;
	if (_target->getTag() != ObjectTag::Player) return false;
	return true;
}

std::string MyGame::EnemyAttackState::randomNextState()
{
	int randomVal = RandomHelper::random_int(0, (int)_randomStates.size() - 1);
	return _randomStates.at(randomVal);
}
