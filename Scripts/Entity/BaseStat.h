#ifndef __BASE_STAT_H__
#define __BASE_STAT_H__

#include "Bonus.h"

namespace MyGame
{
	class Entity;

	class BaseStat
	{
	public:
		void addBonus(Bonus* bonus);
		void removeBonus(Bonus* bonus);
		int getBaseValueRaw();
		int getBaseValue();
		void setBaseValue(int val);
		int getFinalValue();
		void update(float dt);

		BaseStat();
		BaseStat(Entity* owner);
	protected:
		int _finalValue;
		int _fixedValue; 
		int _baseValue;

		CC_SYNTHESIZE(Entity*, _owner, Owner);
		CC_SYNTHESIZE(Stat, _eStat, EStat);
		CC_SYNTHESIZE(std::list<Bonus*>*, _bonuses, Bonuses);
		CC_SYNTHESIZE(int, _growthValue, GrowthValue);
	};
}

#endif // !__BASE_STAT_H__
