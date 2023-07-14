#ifndef __ITEM_INFO_H__
#define __ITEM_INFO_H__

#include "cocos2d.h"

namespace MyGame
{
	class ItemInfo
	{
	protected:
		CC_SYNTHESIZE(int, _itemID, ItemID);
		CC_SYNTHESIZE(int, _amount, Amount);
		CC_SYNTHESIZE(std::string, _itemName, ItemName);
	};
}

#endif // !__ITEM_INFO_H__
