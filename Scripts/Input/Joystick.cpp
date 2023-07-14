#include "Joystick.h"
#include "Input/Input.h"

#define JOYSTICK_OFFSET_X 5.0f
#define JOYSTICK_OFFSET_Y 5.0f


static Point convertCoordinate(Point point) {
	return Director::getInstance()->convertToGL(point);
}

static bool isPointInCircle(Point point, Point center, float radius) {
	float dx = (point.x - center.x);
	float dy = (point.y - center.y);
	return (radius >= sqrt((dx * dx) + (dy * dy)));
}

bool Joystick::init()
{
	if (!Layer::init()) { return false; }

	_kCenter = Point(_joyRadius + JOYSTICK_OFFSET_X,
		_joyRadius + JOYSTICK_OFFSET_Y);
	_velocity = Point::ZERO;
	_enable = true;

	_kCenter = this->getPosition();
	auto listenner = EventListenerTouchOneByOne::create();
	listenner->onTouchBegan = CC_CALLBACK_2(Joystick::onTouchBegan, this);
	listenner->onTouchMoved = CC_CALLBACK_2(Joystick::TouchesMoved, this);
	listenner->onTouchEnded = CC_CALLBACK_2(Joystick::TouchesEnded, this);
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(listenner, this);

	return true;
}

void Joystick::setRenderer(Sprite* bgr, Sprite* thumb, Sprite* direction)
{
	this->_bgr = bgr;
	this->_thumb = thumb;
	this->_direction = direction;
	_joyRadius = _bgr->getContentSize().height / 2 - JOYSTICK_OFFSET_X;
	_thumbRadius = _bgr->getContentSize().height / 2 - _thumb->getContentSize().height / 2 - JOYSTICK_OFFSET_X;
	this->setContentSize(_bgr->getContentSize());
	this->addChild(_bgr, 0);
	this->addChild(_thumb, 2);
}

void Joystick::setThumbStatic(bool isStatic)
{
	this->_thumbStatic = isStatic;
	if (_direction != NULL)
	{
		_direction->removeFromParent();
		if (isStatic)
		{
			this->addChild(_direction, 1);
		}
	}
}

void Joystick::disable()
{
	_enable = false;
	_isPressed = false;
	resetJoystick();
	_velocity = Vec2::ZERO;
}

void Joystick::enable()
{
	_enable = true;
	_isPressed = false;
}

void Joystick::updateVelocity(Point point)
{
	if (!_enable) { return; }
	// calculate Angle and length
	float dx = point.x - this->getPosition().x;
	float dy = point.y - this->getPosition().y;

	float distance = sqrt(dx * dx + dy * dy);
	float angle = atan2(dy, dx); // in radians

	if (distance > _joyRadius)
	{
		dx = cos(angle) * _joyRadius;
		dy = sin(angle) * _joyRadius;
	}

	_velocity = Point(dx / _joyRadius, dy / _joyRadius);

	if (distance > _thumbRadius)
	{
		point.x = this->getPosition().x + cos(angle) * _thumbRadius;
		point.y = this->getPosition().y + sin(angle) * _thumbRadius;
	}

	Vec2 dir = point - this->getPosition();
	if (_thumbStatic)
	{
		dir.normalize();
		dir = dir * _thumbRadius;

		if (_direction != NULL)
		{
			float angle = (Vec2::angle(dir, Vec2(1, 0)));
			if (dir.y < 0) { angle = -angle; }
			_direction->setRotation(CC_RADIANS_TO_DEGREES(angle));
		}
	}

	_thumb->setPosition(dir);
}

void Joystick::resetJoystick()
{
	_isPressed = false;
	this->updateVelocity(this->getPosition());
}

bool Joystick::handleLastTouch()
{
	bool wasPressed = _isPressed;
	if (wasPressed)
	{
		this->resetJoystick();
		_isPressed = false;
	}
	this->setPosition(_originPos);
	return (wasPressed ? true : false);
}

bool Joystick::onTouchBegan(Touch* pTouches, Event* pEvent)
{
	if (!_enable) return false;
	if (_isPressed) { return false; }
	Point point = pTouches->getLocationInView();
	point = convertCoordinate(point);

	if (!_isStatic && abs(_originPos.distance(point)) <= _radiusChange)
	{
		this->setPosition(point);
	}

	if (isPointInCircle(point, this->getPosition(), _joyRadius))
	{
		_isPressed = true;
		this->updateVelocity(point);
	}

	return true;
}

void Joystick::TouchesMoved(Touch* pTouches, Event* pEvent)
{
	if (_isPressed)
	{
		Point point = pTouches->getLocationInView();
		point = convertCoordinate(point);
		this->updateVelocity(point);
	}
}

void Joystick::TouchCancelled(Touch* pTouch, Event* pEvent)
{
	this->handleLastTouch();
}

void Joystick::TouchesEnded(Touch* pTouches, Event* pEvent)
{
	this->handleLastTouch();
}
