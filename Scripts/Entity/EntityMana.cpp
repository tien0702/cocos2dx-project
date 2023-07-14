#include "EntityMana.h"
#include "Entity/Entity.h"

bool MyGame::EntityMana::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->schedule([&](float delta) {
		int mpRecovery = _owner->getEntityStatByID(Stat::MPRecovery)->getBaseValueRaw();
		recovery(mpRecovery);
		}, EntityMana::TimeRecovery * 0.001f, "update_recovery");
	this->retain();
	
	return true;
}

void MyGame::EntityMana::update(float dt)
{
}

bool MyGame::EntityMana::takeMana(int amount)
{
	BaseStat* currentMana = _owner->getEntityStatByID(Stat::CurrentMana);
	int currentManaVal = currentMana->getBaseValue();

	if (currentManaVal < amount) return false;
	currentMana->setBaseValue(currentManaVal - amount);
	// notify all observers
	_owner->notifyAllObserver(EntityObserverType::OnTakeMP);
	return true;
}

void MyGame::EntityMana::recovery(int amount)
{
	BaseStat* currentMana = _owner->getEntityStatByID(Stat::CurrentMana);
	int maxMana = _owner->getEntityStatByID(Stat::MP)->getFinalValue();
	int currentManaVal = currentMana->getBaseValueRaw();

	int calculateVal = currentManaVal + amount;
	calculateVal = std::min(calculateVal, maxMana);
	currentMana->setBaseValue(calculateVal);
	// notify all observers
	_owner->notifyAllObserver(EntityObserverType::OnRecoveryMP);
}

void MyGame::EntityMana::reborn()
{
	BaseStat* currentMana = _owner->getEntityStatByID(Stat::CurrentMana);
	BaseStat* maxMana = _owner->getEntityStatByID(Stat::MP);
	currentMana->setBaseValue(maxMana->getBaseValueRaw());
	// notify all observers
	_owner->notifyAllObserver(EntityObserverType::OnRebornMP);
}
