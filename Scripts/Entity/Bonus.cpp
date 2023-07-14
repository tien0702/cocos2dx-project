#include "Bonus.h"

MyGame::Bonus::Bonus()
{
	_statusEffect = StatusEffect::Buff;
	_modifitype = StatModificationType::Numeric;
	_value = 0;
	_timeStarted = 0;
	_duration = 0;
	_elapsedTime = 0;
}

void MyGame::Bonus::update(float dt)
{
	if (_duration == 0) return;
	_elapsedTime += dt;
}

bool MyGame::Bonus::isEndTime()
{
	if (_duration == 0) return false;
	return (_timeStarted + _duration <= _elapsedTime);
}

MyGame::Bonus* MyGame::Bonus::clone()
{
	Bonus* clone = new Bonus();
	clone->setStatusEff(_statusEffect);
	clone->setStatModifiType(_modifitype);
	clone->setStatBns(_statBns);
	clone->setValueBns(_value);
	clone->setDuration(_duration);
	return clone;
}

int MyGame::Bonus::checkBns()
{
	if (_duration == 0) return 1;
	int result = 0;
	if (_elapsedTime < _timeStarted)
	{
		result = 0;
	}
	else if ((_elapsedTime >= _timeStarted) && (_elapsedTime <= _duration + _timeStarted))
	{
		result = 1;
	}
	else
	{
		result = 2;
	}

	return result;
}
