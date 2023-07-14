#ifndef __BONUS_LEVEL_H__
#define __BONUS_LEVEL_H__

#include "cocos2d.h"

namespace MyGame
{
	enum EachLevel
	{
		EveryLv_1,
		EveryLv_5,
		EveryLv_10,
		EveryLv_20,
		AllLv
	};
	class BonusLevel
	{
	public:
		int getValue(int level);
		BonusLevel();
	private:
		CC_SYNTHESIZE(int, _statID, StatID);
		CC_SYNTHESIZE(std::vector<int>, _values, Values);
	};
}

#endif // !__BONUS_LEVEL_H__
