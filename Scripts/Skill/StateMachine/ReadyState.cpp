#include "ReadyState.h"
#include "Skill/Skill.h"
#include "Entity/Entity.h"

void MyGame::ReadyState::enter(Skill* skill)
{
	_skill = skill;
}

MyGame::SkillStateType MyGame::ReadyState::excute(float dt)
{
	if (!isEnoughMana()) return SkillStateType::Locked;
	if (isPressActivationButton())
	{
		return SkillStateType::Targeting;
	}
	else return SkillStateType::Ready;
}

void MyGame::ReadyState::exit()
{

}

bool MyGame::ReadyState::isEnoughMana()
{
	if(!_skill)
	{
		log("_skill is null");
	}
	auto manaStat = _skill->getStatByID(Stat::ManaCost);
	if(manaStat == nullptr)
	{
		log("Mana cost is nullptr! ");
	}

	int manaNeeded = manaStat->getFinalValue();
	int currentMana = _skill->getOwner()->getEntityStatByID(Stat::CurrentMana)->getFinalValue();
	return (manaNeeded < currentMana);
}

bool MyGame::ReadyState::isPressActivationButton()
{
	InputID id = _skill->getActivationButtonID();
	bool input = PlayerInput::getIns()->getInput(id);
	return input;
}
