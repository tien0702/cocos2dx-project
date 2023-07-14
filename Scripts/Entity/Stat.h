#ifndef __STAT_H__
#define __STAT_H__

#include "cocos2d.h"
USING_NS_CC;

namespace MyGame
{

	enum class StatType
	{
		BaseStatType,
		AdvancedStat,
		ElementalStat
	};

	enum class ValueType
	{
		BothTypesNumbers,
		OnlyPercent,
		OnlyNumber
	};

	class Stat
	{
	public:
		static const int ATK = 1;
		static const int DEF = 2;
		static const int HP = 3;
		static const int MP = 4;
		static const int ATKSpeed = 5;
		static const int MoveSpeed = 6;
		static const int CritRate = 7;
		static const int CritDMG = 8;
		static const int HPRecovery = 9;
		static const int MPRecovery = 10;
		static const int CDReduction = 11;
		static const int SkillDMGBonus = 12;
		static const int PhysicalDMGBonus = 13;
		static const int PhysicalRES = 14;
		static const int PyroDMGBonus = 15;
		static const int PyroRES = 16;
		static const int CryoDMGBonus = 17;
		static const int CryoRES = 18;
		static const int LightningDMGBonus = 19;
		static const int LightningRES = 20;
		static const int CurrentHP = 21;
		static const int CurrentMana = 22;
		static const int RangeFind = 23;
		static const int BreakTime = 24;
		static const int RangeAttack = 25;
		static const int TimeRecheck = 26;
		static const int CastingTime = 27;
		static const int Cooldown = 28;
		static const int Range = 29;
		static const int TimeHold = 30;
		static const int PowerRate = 31;
		static const int Stack = 32;
		static const int RunSpeed = 33;
		static const int TickFrequency = 34;
		static const int SuccessRate = 35;
		static const int AreaRange = 36;
		static const int ActionRange = 37;
		static const int BootTime = 38;
		static const int AreaRadius = 39;
		static const int ManaCost = 40;
		static const int AoEWidth = 41;
		static const int AoEHeight = 42;
		static const int AoERadius = 43;
		static const int MaximumProjectileRange = 44;
	protected:
		CC_SYNTHESIZE(int, _id, ID);
		CC_SYNTHESIZE(StatType, _type, Type);
		CC_SYNTHESIZE(ValueType, _valueType, StatValueType);
		CC_SYNTHESIZE(std::string, _statName, StatName);
		CC_SYNTHESIZE(std::string, _abbreviation, Abbreviation);
		CC_SYNTHESIZE(std::string, _description, Description);
	};
}

#endif // !__STAT_H__
