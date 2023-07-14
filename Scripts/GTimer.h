#ifndef __TIMER_H__
#define __TIMER_H__

#include "cocos2d.h"

USING_NS_CC;

class GTimer : public Node
{
public:
	GTimer();
	void stop();
	void start();
	void reset();

	float getElapsedTime() { return _elapsedTime; }
protected:
	float _elapsedTime;
	virtual void update(float dt);
};

#endif // !__TIMER_H__
