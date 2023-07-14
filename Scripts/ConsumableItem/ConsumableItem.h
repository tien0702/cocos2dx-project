#ifndef __CONSUMABLE_ITEM_H__
#define __CONSUMABLE_ITEM_H__

#include "Inventory/Item/IItemInventory.h"
#include "ConsumableItem/IConsumableItem.h"

namespace MyGame
{
	class Entity;
	class ConsumableItem : public IItemInventory, public IConsumableItem, public Sprite
	{
	public:
		virtual bool init();
		std::string useForTarget(Entity* target);
	};
}

#endif // !__CONSUMABLE_ITEM_H__
