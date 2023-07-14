#include "TargetingStrategy.h"
#include "Skill/Skill.h"
#include "Entity/Entity.h"
#include "Skill/StateMachine/SkillStateMachine.h"
#include "Manager/GameManager.h"

bool MyGame::SkillTargeting::checkInput() const
{
    return PlayerInput::getIns()->getInput(_skill->getActivationButtonID());
}
