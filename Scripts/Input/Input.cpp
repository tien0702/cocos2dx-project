#include "Input.h"

Input* Input::_instance;

Input* Input::getIns()
{
	if (_instance == nullptr)
	{
		_instance = new Input();
		_instance->init();
	}

	return _instance;
}

void Input::resetInput()
{
	_direction = Vec2::ZERO;

	for (auto key : _keyUsed)
	{
		key.second = false;
	}
}

Vec2 Input::getDirection(bool normalize)
{
	if (!_enable) return Vec2::ZERO;
	Vec2 dir = _direction;
	if (normalize) { dir.normalize(); }
	return dir;
}

void Input::setEnable(bool enable)
{
	this->_enable = enable;
}

bool Input::init()
{
	if (!Node::init()) {
		log("init input failed!");
		return false;
	}

	_direction.setZero();
	loadDefaultKey();

	auto eventListenerKeyboard = EventListenerKeyboard::create();
	eventListenerKeyboard->onKeyReleased = CC_CALLBACK_2(Input::onKeyReleased, this);
	eventListenerKeyboard->onKeyPressed = CC_CALLBACK_2(Input::onKeyPress, this);
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(eventListenerKeyboard, this);
	return true;
}

void Input::loadDefaultKey()
{
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_W, false));
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_UP_ARROW, false));
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_S, false));
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_DOWN_ARROW, false));
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_D, false));
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_RIGHT_ARROW, false));
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_A, false));
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_LEFT_ARROW, false));
	_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(EventKeyboard::KeyCode::KEY_SPACE, false));
}

void Input::AddKey(cocos2d::EventKeyboard::KeyCode key)
{
	if (_keyUsed.find(key) == _keyUsed.end())
	{
		_keyUsed.insert(std::pair<EventKeyboard::KeyCode, bool>(key, false));
	}
}

bool Input::GetKey(cocos2d::EventKeyboard::KeyCode key)
{
	if (_keyUsed.find(key) == _keyUsed.end())
	{
		log("Key does not exist!");
		return false;
	}
	return _keyUsed[key];
}

void Input::onKeyPress(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* ev)
{
	if (_keyUsed.find(key) == _keyUsed.end())
		return;
	_keyUsed[key] = true;

	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		_direction.y = 1;
		break;
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		_direction.y = -1;
		break;
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		_direction.x = 1;
		break;
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		_direction.x = -1;
		break;
	default:
		break;
	}
}

void Input::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* ev)
{
	if (_keyUsed.find(key) == _keyUsed.end())
		return;
	_keyUsed[key] = false;

	switch (key)
	{
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (_keyUsed[EventKeyboard::KeyCode::KEY_S] || _keyUsed[EventKeyboard::KeyCode::KEY_DOWN_ARROW])
			_direction.y = -1;
		else
			_direction.y = 0;
		break;
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (_keyUsed[EventKeyboard::KeyCode::KEY_W] || _keyUsed[EventKeyboard::KeyCode::KEY_UP_ARROW])
			_direction.y = 1;
		else _direction.y = 0;
		break;
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (_keyUsed[EventKeyboard::KeyCode::KEY_A] || _keyUsed[EventKeyboard::KeyCode::KEY_LEFT_ARROW])
			_direction.x = -1;
		else _direction.x = 0;
		break;
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		if (_keyUsed[EventKeyboard::KeyCode::KEY_D] || _keyUsed[EventKeyboard::KeyCode::KEY_RIGHT_ARROW])
			_direction.x = 1;
		else _direction.x = 0;
		break;
	default:
		break;
	}
}
