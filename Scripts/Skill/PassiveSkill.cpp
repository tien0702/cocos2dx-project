#include "PassiveSkill.h"
#include "Entity/Entity.h"
#include "ObjectTag.h"

MyGame::PassiveSkill::PassiveSkill()
{
	_needUsed = false;
}

bool MyGame::PassiveSkill::init()
{
	if (!Sprite::init()) {
		log("Init PassiveSkill %s failed", _skillName.c_str());
		return false;
	}

	this->setTag(ObjectTag::ActiveSkill);
	return true;
}

void MyGame::PassiveSkill::onDead()
{
	_needUsed = true;
}

void MyGame::PassiveSkill::onTakingDamage()
{
	_needUsed = true;
}

void MyGame::PassiveSkill::active(Entity* owner)
{
	_elapsedTime = _cooldown;
	_owner->attach(EntityObserverType::OnTakeDame, this);
	_owner->addChild(this);
	this->scheduleUpdate();
}

void MyGame::PassiveSkill::disable()
{
	_owner->dettach(EntityObserverType::OnTakeDame, this);
	_owner->removeFromParent();
	this->unscheduleUpdate();
}

void MyGame::PassiveSkill::useSkill()
{
	_needUsed = false;

	if (_elapsedTime < _cooldown) {
		log("on cooldown!");
		return;
	}
	float ran = RandomHelper::random_real(0.0f, 1.0f);
	if (ran >= _successRate)
	{
		_elapsedTime = 0.0f;
		log("use failed! %0.2lf", ran);
		return;
	}
	log("Use successes! %0.2lf", ran);
	for (auto bns : _bonuses)
	{
		_owner->addBonus(bns->clone());
	}
}

void MyGame::PassiveSkill::update(float dt)
{
	_elapsedTime += dt;
	if (_needUsed) this->useSkill();
}
