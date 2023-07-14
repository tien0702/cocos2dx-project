#include "ActivationStrategy.h"
#include "Skill/Skill.h"
#include "Entity/Entity.h"

void MyGame::SkillActivation::takeMana()
{
	int manaNeeded = _skill->getStatByID(Stat::ManaCost)->getFinalValue();
	_skill->getOwner()->getMana()->takeMana(manaNeeded);
	log("take %d", manaNeeded);
}
