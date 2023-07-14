#include "LockedState.h"
#include "Skill/Skill.h"
#include "Entity/Entity.h"

void MyGame::LockedState::enter(Skill* skill)
{
	_skill = skill;
	updateUIButtonWithState(true);
}

MyGame::SkillStateType MyGame::LockedState::excute(float dt)
{
	if (isEnoughMana()) return SkillStateType::Ready;
	return SkillStateType::Locked;
}

void MyGame::LockedState::exit()
{
	updateUIButtonWithState(false);
}

bool MyGame::LockedState::isEnoughMana()
{
	int manaNeeded = _skill->getStatByID(Stat::ManaCost)->getFinalValue();
	int currentMana = _skill->getOwner()->getEntityStatByID(Stat::CurrentMana)->getFinalValue();
	return (manaNeeded < currentMana);
}

bool MyGame::LockedState::isPressActivationButton()
{
	InputID id = _skill->getActivationButtonID();
	bool input = PlayerInput::getIns()->getInput(id);
	return input;
}

void MyGame::LockedState::updateUIButtonWithState(bool isLocked)
{
	InputID inputID = _skill->getActivationButtonID();
	ButtonSkill* button = PlayerInput::getIns()->getInputSkill(inputID);
	if (isLocked) button->setLocked();
	else button->setReady();
}
