#include "EnemyMoveState.h"
#include "Enemy/Enemy.h"
#include "Entity/DetectEntity.h"
#include "ObjectTag.h"

Vec2 randomPos(Rect rect)
{
	Vec2 pos;
	int minX, minY, maxX, maxY;
	minX = (int)rect.origin.x;
	maxX = (int)rect.origin.x + rect.size.width;
	minY = (int)rect.origin.y;
	maxY = (int)rect.origin.y + rect.size.height;

	pos.x = RandomHelper::random_int(minX, maxX);
	pos.y = RandomHelper::random_int(minY, maxY);

	return pos;
}

void MyGame::EnemyMoveState::enter(Enemy* enemy)
{
	_owner = enemy;
	_moveSpeedStat = enemy->getEntityStatByID(Stat::MoveSpeed);

	_rangeFind = _owner->getEntityStatByID(Stat::RangeFind);
	if (_rangeFind == nullptr)
	{
		log("Failed to get RangleFind Stat");
	}

	// Random position move
	Vec2 moveTo = randomPos(_owner->getEnemySpawnArea());
	this->nextMove(moveTo);
	this->flipXOwner(moveTo);
	_moveTo->retain();

	_owner->runAction(_moveTo);
	_target = DetectEntity::findCharacter();
	// Set animation
	std::string spriteFileName = _owner->getSpriteFileName() + "-" + "move";
	Animation* animation = AnimationCache::getInstance()->getAnimation(spriteFileName);
	_owner->setAnimation(animation);

}

std::string MyGame::EnemyMoveState::updateState(float dt)
{
	// Try get RangeFind Stat
	BaseStat* rangeFind = _owner->getEntityStatByID(Stat::RangeFind);
	if (rangeFind == nullptr)
	{
		log("Failed to get RangleFind Stat");
		return "idle";
	}

	// Check chasing
	if (this->checkChasing()) return "chasing";

	if (_moveTo->isDone())
	{
		_moveTo->autorelease();
		return "idle";
	}

	return "move";
}

void MyGame::EnemyMoveState::exit()
{
	_owner->stopActionByTag(MoveTag);
}

bool MyGame::EnemyMoveState::checkChasing()
{
	if (_target == nullptr) return false;
	if (_target->getTag() != ObjectTag::Player) return false;
	// Check the distance between Owner and target
	float rangeFindVal = _rangeFind->getFinalValue();
	float distance = _target->getPosition().distance(_owner->getPosition());
	if (distance > rangeFindVal) return false;

	// Check Target in AreaSpawn
	if (!_owner->getEnemySpawnArea().containsPoint(_target->getPosition())) return false;

	return true;
}

void MyGame::EnemyMoveState::updateFlipX()
{
	Vec2 dir = _target->getPosition() - _owner->getPosition();
	_owner->getSprite()->setFlippedX(dir.x < 0);
}

void MyGame::EnemyMoveState::nextMove(const Vec2& pos)
{
	float s = pos.distance(_owner->getPosition());
	float t = s / (_owner->getEntityStatByID(Stat::MoveSpeed)->getFinalValue() * 1.0f);

	_moveTo = MoveTo::create(t, pos);
	_moveTo->setTag(MoveTag);
}

void MyGame::EnemyMoveState::flipXOwner(const Vec2& pos)
{
	Vec2 dir = pos - _owner->getPosition();
	if (dir.x == 0) return;

	bool flipX = (dir.x < 0);
	_owner->getSprite()->setFlippedX(flipX);
}
