#ifndef __I_ITEM_INVENTORY_H__
#define __I_ITEM_INVENTORY_H__

#include "cocos2d.h"

USING_NS_CC;

namespace MyGame
{
	enum class EquipableLocation
	{
		Non,
		WeaponLocation,
		RuneTopLocation,
		RuneMiddleLocation,
		RuneBottomLocation
	};

	enum class ItemQuality
	{
		NormalItem,
		RareItem,
		LegendaryItem
	};

	enum class ItemType
	{
		Other,
		WeaponType,
		ComsumableType,
		CollectableType
	};

	class IItemInventory
	{
	protected:
		CC_SYNTHESIZE(int, _id, ID);
		CC_SYNTHESIZE(std::string, _itemName, ItemName);
		CC_SYNTHESIZE(std::string, _description, Description);
		CC_SYNTHESIZE(std::string, _iconPath, IconPath);
		CC_SYNTHESIZE(int, _price, Price);
		CC_SYNTHESIZE(std::vector<float>, _values, ItemValues);
		CC_SYNTHESIZE(float, _weight, Weight);
		CC_SYNTHESIZE(ItemType, _itemType, Type);
		CC_SYNTHESIZE(ItemQuality, _quality, Quality);
		CC_SYNTHESIZE(EquipableLocation, _equipableLocation, ItemEquipableLocation);
	};
}

#endif // !__I_ITEM_INVENTORY_H__
