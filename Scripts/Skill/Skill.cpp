#include "Skill.h"
#include "StateMachine/SkillStateMachine.h"
#include "StateMachine/ReadyState.h"
#include "StateMachine/CooldownState.h"
#include "StateMachine/LockedState.h"
#include "StateMachine/CastingState.h"
#include "StateMachine/TargetingState.h"
#include "UI/Effect.h"

#include "Skill/ActivationStrategy/ProjectileActivation.h"
#include "Skill/ActivationStrategy/AoEActivation.h"

bool MyGame::Skill::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	_stateMachine = new SkillStateMachine(this);
	_stateMachine->addState(SkillStateType::Ready, new ReadyState());
	_stateMachine->addState(SkillStateType::Cooldown, new CooldownState());
	_stateMachine->addState(SkillStateType::Locked, new LockedState());
	_stateMachine->addState(SkillStateType::Targeting, new TargetingState());

	_stateMachine->setDefault(SkillStateType::Ready);
	_stateMachine->init();
	_stateMachine->retain();

	//
	std::string pathEffect = "FHD/Effect/";
	std::string aniName = _info->getEffectName();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(pathEffect + aniName + ".plist", pathEffect + aniName + ".png");

	auto ani = Effect::createAnimation(aniName);
	AnimationCache::getInstance()->addAnimation(ani.first, _info->getSkillName());
	
	this->addChild(_stateMachine);
	this->retain();
	return true;
}

MyGame::BaseStat* MyGame::Skill::getStatByID(int id)
{
	BaseStat* stat = nullptr;
	if (_stats.find(id) != _stats.end())
		stat = _stats.at(id);
	return stat;
}

bool MyGame::Skill::loadAnimation()
{
	return false;
}
