#ifndef __FLOATING_NUMBER_H__
#define __FLOATING_NUMBER_H__

#include "DamagerSystem/DamageMessage.h"
#include "GameConfig.h"

#include "cocos2d.h"

USING_NS_CC;

namespace MyGame
{
	class FloatingNumber
	{
	public:
		static FloatingNumber* getIns();
	public:
		void showDamage(Vec2 targetPos, DamageMessage* data);
		void healHeal(Vec2 targetPos, int amount);
	private:
		TTFConfig _font;
		Sequence* _zoom;
		static FloatingNumber* _instance;
		FloatingNumber();
	};
}

#endif // !__FLOATING_NUMBER_H__
