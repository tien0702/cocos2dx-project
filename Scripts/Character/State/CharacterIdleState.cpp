#include "CharacterIdleState.h"
#include "Character/Character.h"
#include "Input/PlayerInput.h"
#include "Input/Input.h"

void MyGame::CharacterIdleState::enter(Character* owner)
{
	this->_owner = owner;
	this->initAnimation();
}

std::string MyGame::CharacterIdleState::updateState(float dt)
{
	if (this->checkMove()) return "run";
	if (this->checkPrepareDash()) return "prepare-dash";
	return "idle";
}

void MyGame::CharacterIdleState::exit()
{
}

MyGame::CharacterIdleState::CharacterIdleState()
{
}

bool MyGame::CharacterIdleState::initAnimation()
{
	std::string spriteFileName = _owner->getSpriteFileName() + "-" + "idle";
	Animation* animation = AnimationCache::getInstance()->getAnimation(spriteFileName);
	_owner->setAnimation(animation);
	return true;
}

bool MyGame::CharacterIdleState::checkMove()
{
	Vec2 inputDir = Input::getIns()->getDirection(false);

	return (inputDir != Vec2::ZERO);
}

bool MyGame::CharacterIdleState::checkPrepareDash()
{
	if (!PlayerInput::getIns()->getInput(InputID::BT_Skill_Dash)) return false;
	bool result = _owner->getAbilityEquiplocation(ActiveSkillLocation::DashSkill)->canUse();
	return result;
}
