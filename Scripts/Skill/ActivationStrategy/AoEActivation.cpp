#include "AoEActivation.h"
#include "Skill/Skill.h"
#include "Entity/Entity.h"
#include "Character/Character.h"
#include "Skill/StateMachine/SkillStateMachine.h"
#include "ObjectTag.h"
#include "Entity/DetectEntity.h"
#include "Enemy/Enemy.h"
#include "UI/Effect.h"
#include "Bitmask.h"
#include "Manager/GameManager.h"
#include "AudioManager/AudioManager.h"

void MyGame::AoEActivation::activate(Skill* skill, Vec2 position, float rotation, Vec2 direction)
{
	_skill = skill;
	if (!_isLoaded) loadProperties();
	takeMana();
	AudioManager::getIns()->playEffect("Audio/use-skill.mp3");
	Director::getInstance()->getRunningScene()->addChild(this);
	setupForAoE(position);
	playAnimation();
	start();
}

void MyGame::AoEActivation::update(float dt)
{
}

void MyGame::AoEActivation::setupForAoE(Vec2 position)
{
	_skillVisual->setPosition(position);
}

void MyGame::AoEActivation::playAnimation()
{
	std::string animationName = _skill->getInfo()->getEffectName();
	Animation* animation = AnimationCache::getInstance()->getAnimation(animationName);
	Animate* animate = Animate::create(animation);
	animate->setDuration(_skill->getStatByID(Stat::CastingTime)->getFinalValue() * 0.001f);
	_skillVisual->runAction(animate);
}

void MyGame::AoEActivation::dealDamage()
{
	float aoe = _skill->getStatByID(Stat::AoERadius)->getFinalValue();
	auto enemies = DetectEntity::findEnemiesAround(_skillVisual, aoe);

	if (enemies == nullptr) return;
	for (auto enemyNode : *enemies)
	{
		Enemy* enemy = static_cast<Enemy*>(enemyNode);
		if (enemy == nullptr) continue;

		float critRate = _skill->getOwner()->getEntityStatByID(Stat::CritRate)->getFinalValue() * 0.001f;
		DamageMessage* dameData = DamageMessage::calculateDamage(_skill->getOwner(), enemy, *_skill->getSkillPower(), critRate);
		enemy->takeDamage(dameData);
	}
}

void MyGame::AoEActivation::autoExit()
{
	float castingTime = _skill->getStatByID(Stat::CastingTime)->getFinalValue() * 0.001f;
	float bootTime = getBootTime();

	DelayTime* delay = DelayTime::create(castingTime - bootTime);
	auto action = Sequence::createWithTwoActions(delay, CallFunc::create([=]() {exit(); }));
	_skillVisual->runAction(action);
}

void MyGame::AoEActivation::exit()
{
	_skillVisual->removeFromParent();
	_skillVisual->stopAllActions();
	this->removeFromParent();
}

bool MyGame::AoEActivation::loadProperties()
{
	_isLoaded = true;

	// load animation
	std::string path = "FHD/Effect/";
	std::string effectName = _skill->getInfo()->getEffectName();
	Effect::loadAnimationCacheWithFile(path, effectName, effectName);

	// init variable _projectile
	Animation* ani = AnimationCache::getInstance()->getAnimation(effectName)->clone();
	_skillVisual = Sprite::createWithSpriteFrame(ani->getFrames().front()->getSpriteFrame());
	_skillVisual->retain();

	return true;
}

float MyGame::AoEActivation::getBootTime()
{
	return _skill->getStatByID(Stat::BootTime)->getFinalValue() * 0.001f;
}

void MyGame::AoEActivation::start()
{
	DelayTime* bootTime = DelayTime::create(getBootTime());
	auto action = Sequence::createWithTwoActions(bootTime, 
		CallFunc::create([=]() {
			dealDamage();
			AudioManager::getIns()->playEffect("Audio/" + _skill->getInfo()->getEffectName() + ".mp3");
			autoExit(); 
			}));
	_skillVisual->runAction(action);
	GameManager::getIns()->getCurrentMap()->addChild(_skillVisual);
	GameManager::getIns()->getCurrentMap()->setBehindObj(_skillVisual);
}
