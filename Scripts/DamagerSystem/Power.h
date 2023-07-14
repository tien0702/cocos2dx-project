#ifndef __POWER_H__
#define __POWER_H__

#include "cocos2d.h"

namespace MyGame
{
	enum class PowerBy
	{
		Attack,
		MaxHp,
		CurrentHP,
		LoseHp,
		Defense
	};

	enum ElementType
	{
		PhysicalType,
		PyroType,
		CryoType,
		LighningType
	};

	class Power
	{
	public:
		bool initWithStr(std::string valJson);
		int convertIDBnsElement();
		int convertIDResElement();
	private:
		CC_SYNTHESIZE(float, _powerValue, PowerValue);
		CC_SYNTHESIZE(int, _powerNumber, PowerNumber);
		CC_SYNTHESIZE(ElementType, _elementType, ElemType);
		CC_SYNTHESIZE(PowerBy, _powerBy, PBy);
	};
}

#endif // !__POWER_H__
