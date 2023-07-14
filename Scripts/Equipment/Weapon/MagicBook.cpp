#include "MagicBook.h"
#include "Input/PlayerInput.h"
#include "Entity/Entity.h"
#include "Enemy/Enemy.h"
#include "Projectile/ProjectilePool.h"
#include "GameData/ItemData.h"
#include "Entity/DetectEntity.h"
#include "Combat/InfoTargetEnemy.h"

bool MyGame::MagicBook::init()
{
	if (!Sprite::init()) {
		log("Init MagicBook failed!");
		return false;
	}

	_skillWeap = new PassiveSkill();
	_skillWeap->setOwner(_owner);
	_skillWeap->init();

	// Load Properties
	_rangeVisual = DrawNode::create();
	_rangeVisual->retain();

	this->scheduleUpdate();
	_owner->addChild(_rangeVisual);
	return true;
}

void MyGame::MagicBook::initProjectile()
{
	auto data = new GameData::ItemData();
	for (int i = 0; i < ProjectilePool::getIns()->getMaxProjectile(); ++i)
	{
		Projectile* projectile = data->getProjectileByID(_projectileID);
		projectile->init();
		ProjectilePool::getIns()->push(projectile);
	}
}

void MyGame::MagicBook::destroyProjectile()
{
	ProjectilePool::getIns()->destroyProjectile(this->_projectileID);
}

void MyGame::MagicBook::addStateAlloweds(int idState)
{
	auto n = std::find(_stateAlloweds.begin(), _stateAlloweds.end(),
		idState);
	if (n != _stateAlloweds.end())
	{
		_stateAlloweds.push_back(idState);
	}
}

void MyGame::MagicBook::removeStateAlloweds(int idState)
{
	std::remove_if(_stateAlloweds.begin(), _stateAlloweds.end(),
		[=](int& n1) {return n1 == idState; });
}
