#include "GTimer.h"

GTimer::GTimer()
{
	_elapsedTime = 0;
}

void GTimer::stop()
{
	this->unscheduleUpdate();
}

void GTimer::start()
{
	this->scheduleUpdate();
}

void GTimer::reset()
{
	_elapsedTime = 0;
}

void GTimer::update(float dt)
{
	_elapsedTime += dt;
}
