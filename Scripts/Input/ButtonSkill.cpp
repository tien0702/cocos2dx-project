#include "ButtonSkill.h"
#include "Ability/ActiveSkill.h"
#include "GameConfig.h"
#include "Manager/GameManager.h"

static Point convertCoordinate(Point point) {
	return Director::getInstance()->convertToGL(point);
}

static bool isPointInCircle(Point point, Point center, float radius) {
	float dx = (point.x - center.x);
	float dy = (point.y - center.y);
	return (radius >= sqrt((dx * dx) + (dy * dy)));
}

MyGame::ButtonSkill::ButtonSkill()
{
}

bool MyGame::ButtonSkill::init()
{
	if (!Node::init()) {
		log("init Button ActiveSkill failed!");
		return false;
	}

	_iconLock = Sprite::create("FHD/Button/btn-skill-locked.png");
	_iconLock->setVisible(false);

	_border = Sprite::create();
	_button = ui::Button::create();
	_button->setZoomScale(-0.1);

	_joystick = Joystick::create();
	_joystick->setVisible(false);
	_joystick->setStatic(false);
	_timer = new GTimer();

	_button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				_timer->start();
				_joystick->setVisible(true);
				_state = ButtonState::ButtonPress;
				break;
			case cocos2d::ui::Widget::TouchEventType::CANCELED:
				_timer->stop();
				_timer->reset();
				_joystick->setVisible(false);
				_state = ButtonState::None;
				break;
			case cocos2d::ui::Widget::TouchEventType::MOVED:
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				_timer->stop();
				_timer->reset();
				_joystick->setVisible(false);
				_state = ButtonState::None;
				break;
			default:
				break;
			}
		});
	_button->setZoomScale(0);

	//
	TTFConfig font = GameConfig::getIns()->getFont();
	_cooldownOverlay = DrawNode::create();
	_remainingCooldownLb = Label::createWithTTF(font, "0.0");
	_remainingCooldownLb->retain();
	_cooldownOverlay->addChild(_remainingCooldownLb);
	_cooldownOverlay->setVisible(false);
	_button->addChild(_cooldownOverlay, 6);

	this->addChild(_timer, 0);
	this->addChild(_button, 2);
	this->addChild(_border, 1);
	this->addChild(_iconLock, 3);
	this->addChild(_joystick,4);

	this->scheduleUpdate();

	return true;
}

float MyGame::ButtonSkill::getTimeHold()
{
	return _timer->getElapsedTime();
}

MyGame::ButtonState MyGame::ButtonSkill::getState()
{
	return _state;
}

void MyGame::ButtonSkill::setPositionButton(Vec2 pos)
{
	this->_iconLock->setPosition(pos);
	this->_button->setPosition(pos);
	this->_border->setPosition(pos);
	this->_joystick->setPosition(pos);
	this->_joystick->setOriginPos(pos);
}

Vec2 MyGame::ButtonSkill::getDirection()
{
	return _joystick->getVelocity();
}

void MyGame::ButtonSkill::reset()
{
	_joystick->resetJoystick();
	_state = ButtonState::None;
}

void MyGame::ButtonSkill::setLocked()
{
	_iconLock->setVisible(true);
}

void MyGame::ButtonSkill::setReady()
{
	_iconLock->setVisible(false);
}

void MyGame::ButtonSkill::setCooldown(float duration, float maxDuration)
{
	_isCooldown = true;
	_cooldownTime = maxDuration;
	_remainingCooldown = duration;
	_cooldownOverlay->setVisible(true);
	this->scheduleUpdate();
}

bool MyGame::ButtonSkill::initJoystick(std::string bgPath, std::string thumbPath)
{
	Sprite* joySkillBG, * joySkillThumb;

	joySkillBG = Sprite::create(bgPath);
	joySkillThumb = Sprite::create(thumbPath);

	if (joySkillBG == nullptr || joySkillThumb == nullptr) {
		log("init bg or thumb failed!");
		return false;
	}

	_joystick->setRenderer(joySkillBG, joySkillThumb, nullptr);
	return true;
}

bool MyGame::ButtonSkill::setAvatarSkill(std::string normalIMGPath)
{
	_button->loadTextureNormal(normalIMGPath);

	// int overlaye
	Vec2 center = Vec2::ZERO;
	float radius = _button->getContentSize().width / 2;
	float angle = 360.0f;
	unsigned int segments = 360;
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	Color4F color = Color4F(0, 0, 0, 60);

	_cooldownOverlay->drawSolidCircle(center, radius, angle, segments, scaleX, scaleY, color);
	_cooldownOverlay->setPosition(_button->getContentSize() / 2);
	return true;
}

bool MyGame::ButtonSkill::setBackgroundSkillBtn(std::string imgPath)
{
	_border->initWithFile(imgPath);
	_joystick->setRadiusChange(_border->getContentSize().width / 2);
	return _border != nullptr;
}

void MyGame::ButtonSkill::update(float dt)
{
	if (_isCooldown)
	{
		updateCooldown(dt);
	}
}

void MyGame::ButtonSkill::updateUI()
{

}

void MyGame::ButtonSkill::updateCooldown(float dt)
{
	_remainingCooldown -= dt;
	if (_remainingCooldown <= 0)
	{
		_isCooldown = false;
		_cooldownOverlay->setVisible(false);
		this->unscheduleUpdate();
	}
	else
	{
		_remainingCooldownLb->setString(StringUtils::format("%0.2f", _remainingCooldown));
	}
}
