#include "CooldownState.h"
#include "Skill/Skill.h"
#include "Entity/BaseStat.h"
#include "Input/PlayerInput.h"

void MyGame::CooldownState::enter(Skill* skill)
{
	_skill = skill;
	_cooldown = _skill->getStatByID(Stat::Cooldown);
	_remainingCooldown = 0.0f;
	// 
	float cooldown = getCooldown();
	PlayerInput::getIns()->getInputSkill(_skill->getActivationButtonID())->setCooldown(cooldown, getCooldown());
}

MyGame::SkillStateType MyGame::CooldownState::excute(float dt)
{
	_remainingCooldown += dt;
	if (_remainingCooldown >= getCooldown())
		return SkillStateType::Ready;
	return SkillStateType::Cooldown;
}

void MyGame::CooldownState::exit()
{
}

float MyGame::CooldownState::getCooldown()
{
	return _cooldown->getFinalValue() * 0.001f;
}
