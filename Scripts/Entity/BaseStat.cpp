#include "BaseStat.h"
#include "Entity/Entity.h"
#include "Common.h"

void MyGame::BaseStat::addBonus(Bonus* bonus)
{
	if (bonus == NULL) { return; }
	auto find = std::find_if(_bonuses->begin(), _bonuses->end(),
		[&](Bonus* bns) {return bns->getBnsID() == bonus->getBnsID(); });

	// Check bonus exists
	if (find != _bonuses->end())
	{
		log("Bonus exists!");
		if ((*find)->getDuration() == 0) return; // mean no needed to update again

		float time = (*find)->getDuration() - (*find)->getElapsedTime();
		(*find)->setDuration(bonus->getDuration() + time); // update duration
		return;
	}

	if (bonus->getStatModifiType() == StatModificationType::BaseValue)
	{
		_baseValue += bonus->getValueBns();
	}
	else
	{
		_bonuses->push_back(bonus);
	}
}

void MyGame::BaseStat::removeBonus(Bonus* bonus)
{
	if (bonus == NULL) { return; }
	if (bonus->getStatModifiType() == StatModificationType::BaseValue)
	{
		_baseValue -= bonus->getValueBns();
		return;
	}
	auto find = std::find_if(_bonuses->begin(), _bonuses->end(),
		[&](Bonus* bns) {return bns->getBnsID() == bonus->getBnsID(); });
	if (find == _bonuses->end()) return;

	_bonuses->erase(std::remove_if(_bonuses->begin(), _bonuses->end(),
		[=](Bonus* bns) { return bns->getBnsID() == bonus->getBnsID(); }), _bonuses->end());
}

int MyGame::BaseStat::getBaseValueRaw()
{
	return _baseValue;
}

int MyGame::BaseStat::getBaseValue()
{
	if (_owner == nullptr) return _baseValue;
	int bnsLv = _owner->getLevel() * _growthValue;
	return _baseValue + bnsLv;
}

void MyGame::BaseStat::setBaseValue(int val)
{
	_baseValue = val;
}

int MyGame::BaseStat::getFinalValue()
{
	_finalValue = getBaseValue();

	// Get value bonus
	for (auto bns : *_bonuses)
	{
		if (bns->checkBns() != 1) { break; }
		StatModificationType type = bns->getStatModifiType();
		switch (type)
		{
		case MyGame::Percentage:
			_finalValue += getBaseValue() * CONVERT_TO_PERCENT(bns->getValueBns() * 0.01f);
			break;
		case MyGame::Numeric:
			_finalValue += bns->getValueBns();
			break;
		case MyGame::Absolute:
			break;
			_finalValue = bns->getValueBns();
		default:
			break;
		}
	}

	return _finalValue + _fixedValue;
}

void MyGame::BaseStat::update(float dt)
{
	if (_bonuses == NULL || _bonuses->size() == 0) { return; }

	std::list<Bonus*>::iterator it = _bonuses->begin();
	while (it != _bonuses->end())
	{
		(*it)->update(dt);
		if ((*it)->isEndTime())
		{
			it = _bonuses->erase(it);
		}
		else
		{
			++it;
		}
	}
}

MyGame::BaseStat::BaseStat()
{
	_baseValue = 0;
	_finalValue = 0;
	_fixedValue = 0;
	_bonuses = new std::list<Bonus*>();
}

MyGame::BaseStat::BaseStat(Entity* owner)
{
	_owner = owner;
}
