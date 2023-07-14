#ifndef __DAMAGE_MESSAGE_H__
#define __DAMAGE_MESSAGE_H__

#include "DamagerSystem/Power.h"

namespace MyGame
{
	class Entity;
	class Power;
	class DamageMessage
	{
	public:
		static DamageMessage* calculateDamage(Entity* attacker, Entity* victim, Power power, float criteRate);
		int _amount;
		ElementType _elementType;
		bool _isCrit;
	private:
	};
}

#endif // !__DAMAGE_MESSAGE_H__
