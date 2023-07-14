#ifndef __I_INVENTORY_CONTAINER_H__
#define __I_INVENTORY_CONTAINER_H__

#include "cocos2d.h"
#include "Inventory/Item/IItemInventory.h"

namespace MyGame
{
	class IInventoryContainer
	{
	public:
		virtual void addItem(IItemInventory* item) = 0;
		virtual void removeItem(IItemInventory* item) = 0;
	protected:
		// Max Volume = 0 means no limit
		CC_SYNTHESIZE(int, _maxVolume, MaxVolume);
		CC_SYNTHESIZE(std::string, _invName, IvnName);
		CC_SYNTHESIZE(std::string, _invIcon, IvnIcon);
		CC_SYNTHESIZE(std::string, _description, Description);
	};
}

#endif // !__I_INVENTORY_CONTAINER_H__
