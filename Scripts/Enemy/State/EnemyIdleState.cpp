#include "EnemyIdleState.h"
#include "Entity/DetectEntity.h"
#include "Enemy/Enemy.h"


void MyGame::EnemyIdleState::enter(Enemy* enemy)
{
	_owner = enemy;
	_elapsedTime = 0.0f;
	_target = DetectEntity::findCharacter();

	// Try get RangeFind Stat
	_rangeFind = _owner->getEntityStatByID(Stat::RangeFind);
	if (_rangeFind == nullptr)
	{
		log("Failed to get RangleFind Stat");
	}

	// Try get BreakTime Stat
	_breakTime = _owner->getEntityStatByID(Stat::BreakTime);
	if (_breakTime == nullptr)
	{
		log("Failed to get BreakTime Stat");
	}

	std::string spriteFileName = _owner->getSpriteFileName() + "-" + "idle";
	Animation* animation = AnimationCache::getInstance()->getAnimation(spriteFileName);

	_owner->setAnimation(animation);
}

std::string MyGame::EnemyIdleState::updateState(float dt)
{
	_elapsedTime += dt;
	// Check chasing
	if (this->checkChasing()) return "chasing";

	// Check 
	float breakTimeVal = _breakTime->getFinalValue() * 0.01f;
	if (_elapsedTime < breakTimeVal) return "idle";

	return "move";
}

void MyGame::EnemyIdleState::exit()
{
}

bool MyGame::EnemyIdleState::checkChasing()
{
	if (_target == nullptr) return false;
	// Check the distance between Owner and target
	float rangeFindVal = _rangeFind->getFinalValue();
	float distance = _target->getPosition().distance(_owner->getPosition());
	if (distance > rangeFindVal) return false;

	// Check Target in AreaSpawn
	if (!_owner->getEnemySpawnArea().containsPoint(_target->getPosition())) return false;

	return true;
}
