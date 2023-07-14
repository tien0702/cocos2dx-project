#include "TargetingState.h"
#include "Skill/Skill.h"

void MyGame::TargetingState::enter(Skill* skill)
{
	_skill = skill;
	_skill->getTargeting()->target(skill);
}

MyGame::SkillStateType MyGame::TargetingState::excute(float dt)
{
	return SkillStateType::Targeting;
}

void MyGame::TargetingState::exit()
{
}
