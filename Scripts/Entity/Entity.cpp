#include "Entity.h"
#include "UI/Effect.h"
#include "EntityObserver.h"
#include "ui/FloatingNumber.h"

bool MyGame::Entity::init()
{
	if (!Sprite::init()) { return false; }

	// Health point
	_entityHealth = new EntityHealth();
	_entityHealth->setMaxHp(this->getEntityStatByID(Stat::HP));
	_entityHealth->setHp(this->getEntityStatByID(Stat::CurrentHP));
	_entityHealth->setOwner(this);
	_entityHealth->init();

	// MP
	_entityMana = new EntityMana();
	_entityMana->setOwner(this);
	_entityMana->init();

	// addchild
	this->addChild(_entityHealth);
	this->addChild(_entityMana);
	this->scheduleUpdate();
	return true;
}

void MyGame::Entity::takeDamage(DamageMessage* data)
{
	_entityHealth->takeDamage(data);
	FloatingNumber::getIns()->showDamage(_position, data);
	if (_entityHealth->isDead())
		this->notifyAllObserver(EntityObserverType::OnDie);
}

void MyGame::Entity::addStat(BaseStat* newStat)
{
	if (_stats == NULL) { _stats = new std::list<BaseStat*>(); }

	auto findStat = std::find_if(_stats->begin(), _stats->end(),
		[&](BaseStat* stat) {
			return stat->getEStat().getID() == newStat->getEStat().getID();
		});

	if (findStat != _stats->end())
		_stats->push_back(newStat);
	else
		log("stat %s already exists!", (newStat->getEStat().getStatName().c_str()));
}

void MyGame::Entity::addBonus(Bonus* bns)
{
	if (bns == nullptr) return;
	if (bns->getStatBns().getID() == Stat::CurrentHP)
	{
		_entityHealth->recovery(bns->getValueBns());
		return;
	}
	else if (bns->getStatBns().getID() == Stat::CurrentMana)
	{
		_entityMana->recovery(bns->getValueBns());
		return;
	}
	auto findStat = std::find_if(_stats->begin(), _stats->end(),
		[&](BaseStat* stat) {
			return stat->getEStat().getID() == bns->getStatBns().getID();
		});

	if (findStat != _stats->end())
		(*findStat)->addBonus(bns);
	else
	{
		log("stat %s not found!", bns->getStatBns().getStatName().c_str());
	}

	if (bns->getStatBns().getID() == Stat::HP)
	{
		this->notifyAllObserver(EntityObserverType::OnRecoveryHP);
	}
}

void MyGame::Entity::removeBonus(Bonus* bns)
{
	int id = bns->getStatBns().getID();
	auto findStat = std::find_if(_stats->begin(), _stats->end(),
		[&](BaseStat* stat) {
			return stat->getEStat().getID() == id;
		});

	if (findStat != _stats->end())
	{
		(*findStat)->removeBonus(bns);
	}
}

std::string MyGame::Entity::equipItem(IItemInventory* item)
{
	return std::string();
}

MyGame::BaseStat* MyGame::Entity::getEntityStatByID(int id)
{
	auto findStat = std::find_if(_stats->begin(), _stats->end(),
		[&](BaseStat* stat) {
			return stat->getEStat().getID() == id;
		});
	return (*findStat);
}

void MyGame::Entity::spawn()
{
}

void MyGame::Entity::setAnimation(std::string animationName)
{
	animationName = _spriteFileName + "-" + animationName;
	_sprite->stopActionsByFlags(Entity::AnimationTag);

	Animation* aniTarget = AnimationCache::getInstance()->getAnimation(animationName);
	RepeatForever* ani = RepeatForever::create(Animate::create(aniTarget));
	ani->setFlags(Entity::AnimationTag);
	_sprite->runAction(ani);
}

void MyGame::Entity::setAnimation(std::string animationName, float time)
{
	animationName = _spriteFileName + "-" + animationName;
	_sprite->stopActionsByFlags(Entity::AnimationTag);

	Animation* aniTarget = AnimationCache::getInstance()->getAnimation(animationName);
	auto c = time / (float(aniTarget->getFrames().size()));
	aniTarget->setDelayPerUnit(time / (float(aniTarget->getFrames().size())));
	RepeatForever* ani = RepeatForever::create(Animate::create(aniTarget));
	ani->setFlags(Entity::AnimationTag);
	_sprite->runAction(ani);
}

void MyGame::Entity::setAnimation(Animation* animation)
{
	_sprite->stopActionsByFlags(Entity::AnimationTag);

	RepeatForever* ani = RepeatForever::create(Animate::create(animation));
	ani->setFlags(Entity::AnimationTag);
	_sprite->runAction(ani);
}

void MyGame::Entity::setStats(std::list<BaseStat*>* statas)
{
	for (BaseStat* stat : *statas)
	{
		stat->setOwner(this);
	}

	this->_stats = statas;
}

void MyGame::Entity::setStates(std::vector<std::string> states)
{
	_states = states;
}

int MyGame::Entity::getCurrentStateID()
{
	return 0;
}

bool MyGame::Entity::loadProperties()
{
	return false;
}

bool MyGame::Entity::initAnimation()
{
	return true;
}

void MyGame::Entity::update(float dt)
{

}
