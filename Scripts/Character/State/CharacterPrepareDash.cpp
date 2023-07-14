#include "CharacterPrepareDash.h"
#include "Character/Character.h"
#include "Input/PlayerInput.h"
#include "Input/Input.h"
#include "Input/ButtonSkill.h"
#include "Entity/BaseStat.h"

void MyGame::CharacterPrepareDash::enter(Character* owner)
{
	this->_owner = owner;
	this->loadProperties();
	this->initAnimation();
}

std::string MyGame::CharacterPrepareDash::updateState(float dt)
{
	_elapsedTime += dt;

	this->flipX();
	this->updatePowerBar();
	if (this->checkInput()) return "dash";
	_timeHold = _targetInput->getTimeHold();

	return "prepare-dash";
}

void MyGame::CharacterPrepareDash::exit()
{
	_powerBar->removeFromParent();
}

MyGame::CharacterPrepareDash::CharacterPrepareDash()
{
	std::string bgPath, progressPath;
	bgPath = "FHD/ProgressBar/power-bar-border.png";
	progressPath = "FHD/ProgressBar/power-bar-progress.png";
	Sprite* bgProgress = Sprite::create(bgPath);
	_powerBar = ui::LoadingBar::create(progressPath);
	_powerBar->setDirection(ui::LoadingBar::Direction::LEFT);
	_powerBar->retain();

	bgProgress->setPosition(_powerBar->getContentSize() / 2);
	_powerBar->addChild(bgProgress);
}

bool MyGame::CharacterPrepareDash::initAnimation()
{
	std::string spriteFileName = _owner->getSpriteFileName() + "-" + "prepare-dash";
	Animation* animation = AnimationCache::getInstance()->getAnimation(spriteFileName)->clone();
	_owner->setAnimation(animation);

	return true;
}

bool MyGame::CharacterPrepareDash::loadProperties()
{
	Vec2 pos;
	pos.x = 0;
	pos.y = _owner->getEntitySize().height / 2 + _powerBar->getContentSize().height / 2;
	_powerBar->setPosition(pos);
	_owner->addChild(_powerBar);

	_timeHold = 0.0f;
	_targetInput = PlayerInput::getIns()->getInputSkill(InputID::BT_Skill_Dash);
	_dashAbility = _owner->getAbilityEquiplocation(ActiveSkillLocation::DashSkill);
	_originalTimeHold = (_dashAbility->getStatByID(Stat::TimeHold)->getFinalValue()) * 0.001f;
	_originalTimeHold *= 0.5f;

	_powerBar->setPercent(100);
	_maxTimeHold = (_dashAbility->getStatByID(Stat::TimeHold)->getFinalValue()) * 0.001f;
	return true;
}

void MyGame::CharacterPrepareDash::updatePowerBar()
{
	float percent = _timeHold/ (_maxTimeHold - _originalTimeHold);
	_powerBar->setPercent(percent * 100.0f);
}

void MyGame::CharacterPrepareDash::flipX()
{
	Vec2 dir = Input::getIns()->getDirection(false);
	if (dir.x != 0) _owner->getSprite()->setFlippedX(dir.x > 0);
}

bool MyGame::CharacterPrepareDash::checkInput()
{
	bool input = PlayerInput::getIns()->getInput(InputID::BT_Skill_Dash);
	if (!input)
	{
		if (_originalTimeHold + _timeHold > _maxTimeHold)
		{
			_timeHold = _maxTimeHold - _originalTimeHold;
		}
		this->updatePowerRate();
		return true;
	}
	return false;
}

void MyGame::CharacterPrepareDash::updatePowerRate()
{
	_dashAbility->getStatByID(Stat::PowerRate)->setBaseValue((_timeHold + _originalTimeHold) * 100.0f);
}
