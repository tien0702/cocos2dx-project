#include "EntityHealth.h"
#include "Entity/BaseStat.h"
#include "ui/FloatingNumber.h"
#include "Entity/Entity.h"


bool MyGame::EntityHealth::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->scheduleUpdate();
	this->schedule([&](float delta) {
		int hpRecovery = _owner->getEntityStatByID(Stat::HPRecovery)->getBaseValueRaw();
		recovery(hpRecovery);
		}, EntityHealth::TimeRecovery * 0.001f, "update_recovery");
	this->retain();
	return true;
}

void MyGame::EntityHealth::update(float dt)
{
	if (_isInvulnerable)
	{
		_timeSinceLastHit += dt;
		if (_timeSinceLastHit > _invulnerabiltyTime)
		{
			_timeSinceLastHit = 0.0f;
			_isInvulnerable = false;
		}
	}
}

void MyGame::EntityHealth::takeDamage(DamageMessage* data)
{
	int maxHP = _maxHp->getBaseValueRaw();
	int hp = _hp->getBaseValueRaw();

	if (hp <= 0 || _isInvulnerable)
		return;

	int newhp = hp - data->_amount;
	newhp = std::max(newhp, 0);
	_hp->setBaseValue(newhp);

	// notify on take dame observer
	_owner->notifyAllObserver(EntityObserverType::OnTakeDame);
	// notify on die observer
	if (hp == 0)
		_owner->notifyAllObserver(EntityObserverType::OnDie);
}

void MyGame::EntityHealth::reborn()
{
	_hp->setBaseValue(_maxHp->getFinalValue());
	// Notify all observers
	_owner->notifyAllObserver(EntityObserverType::OnRebornHP);
}

void MyGame::EntityHealth::recovery(int hp)
{
	int curHp = _hp->getBaseValueRaw();
	_hp->setBaseValue(curHp + hp);
	int maxHp = _maxHp->getFinalValue();
	if (_hp->getBaseValueRaw() > maxHp) _hp->setBaseValue(maxHp);

	// Notify all observer
	_owner->notifyAllObserver(EntityObserverType::OnRecoveryHP);
}

bool MyGame::EntityHealth::isDead()
{
	return _hp->getFinalValue() <= 0;
}
