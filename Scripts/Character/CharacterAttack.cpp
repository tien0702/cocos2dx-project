#include "CharacterAttack.h"
#include "Entity/DetectEntity.h"
#include "Character/Character.h"
#include "Enemy/Enemy.h"
#include "Input/PlayerInput.h"
#include "Projectile/ProjectilePool.h"
#include "Combat/InfoTargetEnemy.h"

#include "Character/State/CharacterStateMachine.h"


bool MyGame::CharacterAttack::init()
{
	if (!Node::init()) {
		log("Init Character Attack failed!");
		return false;
	}

	if (!loadProperties()) {
		log("Load properties CharacterAttack failed!");
		return false;
	}

	_character->addChild(_rangeVisual, 1);
	this->scheduleUpdate();
	return true;
}

MyGame::CharacterAttack::CharacterAttack(Character* character)
{
	_character = character;
}

void MyGame::CharacterAttack::update(float dt)
{
	_elapsedTime += dt;
	bool input = PlayerInput::getIns()->getInput(InputID::BT_NormalATK);
	_rangeVisual->setVisible(input);
	if (!input) return;
	if (onCooldown()) return;
	//if (!stateAbleAttack()) return;

	this->attack(this->findTarget());
}

void MyGame::CharacterAttack::attack(Node* target)
{
	if (target == nullptr) return;
	// Triggered
	Projectile* projectile = ProjectilePool::getIns()->get(_weapon->getProjectileID());
	projectile->setOwner(_character);
	Vec2 direction = target->getPosition() - _character->getPosition();
	projectile->triggered(direction, _character->getPosition());

	_character->getSprite()->setFlippedX(direction.x > 0);
	_character->getStateMachine()->setState("attack");

	// Show info
	Enemy* enemy = static_cast<Enemy*>(target);
	if (enemy != nullptr)
		InfoTargetEnemy::getIns()->changeTarget(enemy);

	_elapsedTime = 0.0f;
}

bool MyGame::CharacterAttack::loadProperties()
{
	if (_character == nullptr) return false;
	_weapon = _character->getWeapon();
	_attackSpeed = _character->getEntityStatByID(Stat::ATKSpeed);
	_elapsedTime = 1000.0f / (_attackSpeed->getFinalValue() * 1.0f);

	_range = _character->getWeapon()->getRange();
	_rangeVisual = DrawNode::create();
	_rangeVisual->drawCircle(Vec2::ZERO, _range, 360.0f, 360, false, Color4F::WHITE);
	_rangeVisual->setVisible(false);
	_rangeVisual->retain();
	return true;
}

bool MyGame::CharacterAttack::onCooldown()
{
	float cooldown = 1000.0f / (_attackSpeed->getFinalValue() * 1.0f);
	return (_elapsedTime < cooldown);
}

bool MyGame::CharacterAttack::stateAbleAttack()
{
	std::list<int> stateAlloweds = _character->getWeapon()->getStateAlloweds();
	int curState = _character->getCurrentStateID();
	auto result = std::find(stateAlloweds.begin(), stateAlloweds.end(), curState);
	if (result == stateAlloweds.end()) return false;
	return true;
}

Node* MyGame::CharacterAttack::findTarget()
{
	Node* target = DetectEntity::getNearestEnemy(_character, _character->getWeapon()->getRange());
	return target;
}
