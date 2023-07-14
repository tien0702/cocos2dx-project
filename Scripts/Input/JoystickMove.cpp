#include "JoystickMove.h"
#include "Input/Input.h"

JoystickMove* JoystickMove::_instance;

JoystickMove* JoystickMove::getIns()
{
	if (_instance == nullptr)
	{
		_instance = new JoystickMove();
		_instance->init();
	}

	return _instance;
}

bool JoystickMove::init()
{
	if (!Joystick::init()) {
		log("init joystick move failed!");
		return false;
	}

	return true;
}

void JoystickMove::updateVelocity(Point point)
{
	Joystick::updateVelocity(point);
	Input::getIns()->_direction = _velocity;
}
