#ifndef __BONUS_H__
#define __BONUS_H__

#include "Stat.h"

namespace MyGame
{

	enum StatModificationType
	{
		Percentage,
		Numeric,
		Absolute,
		BaseValue
	};

	enum StatusEffect
	{
		Buff,
		Debuff
	};

	class Bonus
	{
	public:
		Bonus();
		void update(float dt);
		bool isEndTime();
		Bonus* clone();
		/// <summary>
		/// <para>0 = Not started yet</para> 
		/// <para>1 = In process</para> 
		/// <para>2 = Finished</para>
		/// </summary>
		int checkBns();
	protected:
		CC_SYNTHESIZE(StatusEffect, _statusEffect, StatusEff);
		CC_SYNTHESIZE(StatModificationType, _modifitype, StatModifiType);
		CC_SYNTHESIZE(Stat, _statBns, StatBns);
		CC_SYNTHESIZE(int, _id, BnsID);
		CC_SYNTHESIZE(int, _value, ValueBns);
		CC_SYNTHESIZE(float, _timeStarted, TimeStarted);
		CC_SYNTHESIZE(float, _duration, Duration);
		CC_SYNTHESIZE(float, _elapsedTime, ElapsedTime);
	};
}

#endif // !__BONUS_H__
