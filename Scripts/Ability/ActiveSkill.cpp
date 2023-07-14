#include "ActiveSkill.h"
#include "Entity/BaseStat.h"

bool MyGame::ActiveSkill::init()
{
	if (!Node::init()) {
		log("Init ActiveSkill Failed!");
		return false;
	}

	_stack = 0;
	_elapsedTime = 0.0f;

	this->scheduleUpdate();
	return true;
}

MyGame::ActiveSkill::ActiveSkill()
{

}

bool MyGame::ActiveSkill::canUse()
{
	if (_stack == 0) return false;
	if (!_canUse) return false;

	return true;
}

bool MyGame::ActiveSkill::isReady()
{
	return false;
}

bool MyGame::ActiveSkill::use()
{
	_canUse = false;
	_stack -= 1;
	this->cooldownStart();
	return true;
}

void MyGame::ActiveSkill::addStat(BaseStat* newStat)
{
	// Check value null
	if (newStat == nullptr) return;
	if (_abilityStats == nullptr) _abilityStats = new std::map<int, BaseStat*>();

	// Check Stat exists
	if (this->statExists(newStat->getEStat().getID()))
	{
		log("Stat exists!");
		return;
	}

	// Add Stat
	auto val = std::pair<int, BaseStat*>(newStat->getEStat().getID(), newStat);
	_abilityStats->insert(val);
}

void MyGame::ActiveSkill::removeStat(int statID)
{
	if (this->statExists(statID))
	{
		log("Stat not exists!");
		return;
	}

	_abilityStats->erase(statID);
}

void MyGame::ActiveSkill::setStats(std::map<int, BaseStat*>* abilityStats)
{
	this->_abilityStats = abilityStats;
}

MyGame::BaseStat* MyGame::ActiveSkill::getStatByID(int id)
{
	if (!this->statExists(id))
	{
		log("Stat not exists!");
		return nullptr;
	}
	return _abilityStats->at(id);
}

bool MyGame::ActiveSkill::statExists(int id)
{
	return (_abilityStats->find(id) != _abilityStats->end());
}

void MyGame::ActiveSkill::update(float dt)
{
	_elapsedTime += dt;
}

void MyGame::ActiveSkill::completedCooldown()
{
	_elapsedTime = 0.0f;
	_canUse = true;

	// Check stack
	BaseStat* stackVal = this->getStatByID(Stat::Stack);
	if (stackVal == nullptr) return;
	int maxStack = stackVal->getFinalValue();
	if (_stack < maxStack)
	{
		_stack += 1;
		this->cooldownStart();
	}
}

void MyGame::ActiveSkill::cooldownStart()
{
	float cooldown = this->getStatByID(Stat::Cooldown)->getFinalValue() * 0.001f;

	DelayTime* delay = DelayTime::create(cooldown);
	CallFunc* completed = CallFunc::create([&]() {this->completedCooldown(); });
	Sequence* startCooldown = Sequence::createWithTwoActions(delay, completed);

	this->runAction(startCooldown);
}
