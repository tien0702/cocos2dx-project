#include "ButtonNormalATK.h"

MyGame::ButtonNormalATK* MyGame::ButtonNormalATK::_instance;

MyGame::ButtonNormalATK::ButtonNormalATK()
{
}

bool MyGame::ButtonNormalATK::init()
{
	if (!ui::Button::init()) {
		log("init Button Normal ATK failed!");
		return false;
	}

	_timer = new GTimer();
	_state = ButtonState::None;
	this->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				_timer->start();
				_state = ButtonState::ButtonPress;
				break;
			case cocos2d::ui::Widget::TouchEventType::CANCELED:
				_timer->stop();
				_timer->reset();
				_state = ButtonState::None;
				break;
			case cocos2d::ui::Widget::TouchEventType::MOVED:
				//_state = ButtonState::ButtonHold;
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				_timer->stop();
				_timer->reset();
				_state = ButtonState::None;
				break;
			default:
				break;
			}
		});

	this->addChild(_timer);
	return true;
}

MyGame::ButtonNormalATK* MyGame::ButtonNormalATK::getIns()
{
	if (_instance == nullptr) {
		_instance = new ButtonNormalATK();
		_instance->init();
	}

	return _instance;
}

float MyGame::ButtonNormalATK::getTimeHold()
{
	return _timer->getElapsedTime();
}

MyGame::ButtonState MyGame::ButtonNormalATK::getState()
{
	return _state;
}
