#ifndef __I_WEAPON_H__
#define __I_WEAPON_H__

#include "cocos2d.h"
#include "DamagerSystem/Power.h"
#include "DamagerSystem/Power.h"

namespace MyGame
{
	class Entity;
	class Bonus;

	enum class WeaponType
	{
		MagicBookType
	};

	class IWeapon
	{
	public:
	protected:
		// Fixed stat
		CC_SYNTHESIZE(int, _bnsATK, BnsATK);
		CC_SYNTHESIZE(Bonus*, _statBns, StatBonus);
		CC_SYNTHESIZE(WeaponType, _type, WeapType);
		CC_SYNTHESIZE(Power, _power, WeapPower);
		CC_SYNTHESIZE(float, _range, Range);
		CC_SYNTHESIZE(bool, _isEquip, IsEquip);
	};
}

#endif // !__I_WEAPON_H__
