#include "PlayerInput.h"
#include "Input/Input.h"
#include "Manager/GameManager.h"

MyGame::PlayerInput* MyGame::PlayerInput::_instance;

MyGame::PlayerInput* MyGame::PlayerInput::getIns()
{
	if (_instance == nullptr) {
		_instance = new PlayerInput();
		_instance->init();
	}

	return _instance;
}

MyGame::PlayerInput::PlayerInput()
{

}

bool MyGame::PlayerInput::getInput(InputID id)
{
	if (!_enable) return false;
	bool result = false;
	switch (id)
	{
	case MyGame::InputID::BT_NormalATK:
		result = (_buttonNormalATK->getState() == ButtonState::ButtonPress);
		break;
	case MyGame::InputID::BT_JoystickMove:
		break;
	case MyGame::InputID::BT_Skill_Ultimate:
		result = (_ultimate->getState() == ButtonState::ButtonPress);
		break;
	case MyGame::InputID::BT_Skill_Talen:
		result = (_talen->getState() == ButtonState::ButtonPress);
		break;
	case MyGame::InputID::BT_Skill_Dash:
		result = (_evade->getState() == ButtonState::ButtonPress);
		break;
	default:
		break;
	}

	return result;
}

void MyGame::PlayerInput::cleanInput()
{
	_joystickMove->resetJoystick();
	Input::getIns()->resetInput();
}

void MyGame::PlayerInput::waitInDuration(float duration)
{
	this->disable();
	this->runAction(Sequence::createWithTwoActions(DelayTime::create(duration),
		CallFunc::create([=]() {this->enable(); })));
}

void MyGame::PlayerInput::disable()
{
	Input::getIns()->setEnable(false);
	_enable = false;
	_joystickMove->disable();
}

void MyGame::PlayerInput::enable()
{
	_enable = true;
	Input::getIns()->setEnable(true);
	_joystickMove->enable();
}

bool MyGame::PlayerInput::isEnable()
{
	return _enable;
}

void MyGame::PlayerInput::reloadSkillBtns()
{
	std::string ultiStr = "FHD/Icon/" + GameManager::getIns()->getCharacter()->getSkillEquiplocation(ActiveSkillLocation::UltimateSkill)->getInfo()->getIconName() + ".png";
	_ultimate->setAvatarSkill(ultiStr);

	std::string skillStr = "FHD/Icon/" + GameManager::getIns()->getCharacter()->getSkillEquiplocation(ActiveSkillLocation::TalenSkill)->getInfo()->getIconName() + ".png";
	_talen->setAvatarSkill(skillStr);
}

MyGame::ButtonSkill* MyGame::PlayerInput::getInputSkill(InputID id)
{
	ButtonSkill* result = nullptr;
	switch (id)
	{
	case MyGame::InputID::BT_Skill_Ultimate:
		result = _ultimate;
		break;
	case MyGame::InputID::BT_Skill_Talen:
		result = _talen;
		break;
	case MyGame::InputID::BT_Skill_Dash:
		result = _evade;
		break;
	}

	return result;
}

float MyGame::PlayerInput::getInputTime(InputID id)
{
	if (!_enable) return false;
	float result = 0.0f;
	switch (id)
	{
	case MyGame::InputID::BT_NormalATK:
		result = _buttonNormalATK->getTimeHold();
		break;
	case MyGame::InputID::BT_JoystickMove:
		break;
	case MyGame::InputID::BT_Skill_Ultimate:
		result = _ultimate->getTimeHold();
		break;
	case MyGame::InputID::BT_Skill_Talen:
		result = _talen->getTimeHold();
		break;
	case MyGame::InputID::BT_Skill_Dash:
		result = _evade->getTimeHold();
		break;
	default:
		break;
	}

	return result;
}

bool MyGame::PlayerInput::init()
{
	if (!Layer::init()) {
		log("init Player Input failed!");
		return false;
	}

	Size winSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	float border = 150, marginNormalATK = 70, disSkill = 40, angleSkill = 45;
	std::string borderPath, iconPath, joyBgPath, joyThumbPath, normalATKPath;
	Vec2 posJoyMove, posNormalATK, posUlti, posTalen, posEvade, axisSkill;

	_joystickMove = JoystickMove::getIns();
	_buttonNormalATK = ButtonNormalATK::getIns();
	_ultimate = new ButtonSkill();
	_talen = new ButtonSkill();
	_evade = new ButtonSkill();


	// Path
	borderPath = "FHD/Background/border-skill.png";
	iconPath = "FHD/Background/iconTemp.png";
	joyBgPath = "FHD/Background/joystick-bg.png";
	joyThumbPath = "FHD/Background/joystick-thumb.png";
	normalATKPath = "FHD/Button/button-normal-atk.png";

	// Joystick Move
	Sprite* bg, * thumb, * dir;
	bg = Sprite::create("FHD/Mics/joy-move-bg.png");
	thumb = Sprite::create("FHD/Mics/joy-move-thumb.png");
	dir = Sprite::create("FHD/Mics/joy-move-dir.png");

	_joystickMove = JoystickMove::getIns();
	_joystickMove->setRenderer(bg, thumb, dir);
	_joystickMove->setThumbStatic(true);
	_joystickMove->setStatic(false);

	// button normal ATK
	_buttonNormalATK = ButtonNormalATK::getIns();
	_buttonNormalATK->loadTextureNormal(normalATKPath);

	// Buttons ActiveSkill
	_ultimate->init();
	_talen->init();
	_evade->init();

	_ultimate->setBackgroundSkillBtn(borderPath);
	std::string ultiStr = "FHD/Icon/" + GameManager::getIns()->getCharacter()->getSkillEquiplocation(ActiveSkillLocation::UltimateSkill)->getInfo()->getIconName() + ".png";
	_ultimate->setAvatarSkill(ultiStr);
	_ultimate->initJoystick(joyBgPath, joyThumbPath);

	_talen->setBackgroundSkillBtn(borderPath);
	std::string skillStr = "FHD/Icon/" + GameManager::getIns()->getCharacter()->getSkillEquiplocation(ActiveSkillLocation::TalenSkill)->getInfo()->getIconName() + ".png";
	_talen->setAvatarSkill(skillStr);
	_talen->initJoystick(joyBgPath, joyThumbPath);

	_evade->setBackgroundSkillBtn(borderPath);
	_evade->setAvatarSkill(iconPath);
	_evade->initJoystick(joyBgPath, joyThumbPath);

	std::string path = GameManager::getIns()->getCharacter()->getAbilityEquiplocation(ActiveSkillLocation::DashSkill)->getIconPath();
	path = "FHD/Icon/" + path + ".png";
	_evade->setAvatarSkill(path);	

	// Postion
	posJoyMove.x = _joystickMove->getContentSize().width / 2 + border;
	posJoyMove.y = _joystickMove->getContentSize().height / 2 + border;

	posNormalATK.x = winSize.width - (_buttonNormalATK->getContentSize().width / 2 + marginNormalATK);
	posNormalATK.y = _buttonNormalATK->getContentSize().height / 2 + marginNormalATK;
	
	axisSkill.x = posNormalATK.x;
	axisSkill.y = posNormalATK.y + _buttonNormalATK->getContentSize().width + disSkill;

	posUlti = axisSkill.rotateByAngle(posNormalATK, CC_DEGREES_TO_RADIANS(angleSkill * 0));
	posTalen = axisSkill.rotateByAngle(posNormalATK, CC_DEGREES_TO_RADIANS(angleSkill * 1));
	posEvade = axisSkill.rotateByAngle(posNormalATK, CC_DEGREES_TO_RADIANS(angleSkill * 2));

	_joystickMove->setOriginPos(posJoyMove);
	_joystickMove->setPosition(posJoyMove);

	_buttonNormalATK->setPosition(posNormalATK);
	_ultimate->setPositionButton(posUlti);
	_talen->setPositionButton(posTalen);
	_evade->setPositionButton(posEvade);

	this->addChild(_joystickMove);
	this->addChild(_buttonNormalATK);
	this->addChild(_ultimate);
	this->addChild(_talen);
	this->addChild(_evade);

	return true;
}
