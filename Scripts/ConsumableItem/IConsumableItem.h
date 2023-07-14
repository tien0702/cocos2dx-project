#ifndef __I_CONSUMABLE_ITEM_H__
#define __I_CONSUMABLE_ITEM_H__

#include "cocos2d.h"
#include "Entity/Bonus.h"

namespace MyGame
{
	class IConsumableItem
	{
	protected:
		CC_SYNTHESIZE(int, _quantity, Quantity);
		CC_SYNTHESIZE(Bonus*, _bonus, ItemBonus);
	};
}

#endif // !__I_CONSUMABLE_ITEM_H__
