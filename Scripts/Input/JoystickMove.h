#ifndef __JOYSTICK_MOVE_H__
#define __JOYSTICK_MOVE_H__

#include "Input/Joystick.h"

class JoystickMove : public Joystick
{
public:
	static JoystickMove* getIns();

protected:
	virtual bool init();
	static JoystickMove* _instance;
	virtual void updateVelocity(Point point);
};

#endif // !__JOYSTICK_MOVE_H__
