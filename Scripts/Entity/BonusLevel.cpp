#include "BonusLevel.h"

int MyGame::BonusLevel::getValue(int level)
{
	int result = 0;

	// get bonus every 1 lv
	if (_values.at(EachLevel::EveryLv_1) != 0)
		result += level * _values.at(EachLevel::EveryLv_1);

	// get bonus every 5 lv
	if (_values.at(EachLevel::EveryLv_5) != 0)
		result += (level / 5) * _values.at(EachLevel::EveryLv_5);

	// get bonus every 10 lv
	if (_values.at(EachLevel::EveryLv_10) != 0)
		result += (level / 10) * _values.at(EachLevel::EveryLv_10);

	// get bonus every 20 lv
	if (_values.at(EachLevel::EveryLv_20) != 0)
		result += (level / 20) * _values.at(EachLevel::EveryLv_20);

	return result;
}

MyGame::BonusLevel::BonusLevel()
{
	for (int i = 0; i < EachLevel::AllLv; ++i)
	{
		_values.push_back(0);
	}
}
