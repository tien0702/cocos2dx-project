#ifndef __ITEM_SHOP_SLOT_H__
#define __ITEM_SHOP_SLOT_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Inventory/Item/IItemInventory.h"

USING_NS_CC;

namespace MyGame
{
	class ItemShopSlot : public ui::Button
	{
	public:
		static ItemShopSlot* create(IItemInventory* item);
		void updateComponent();
	private:
		bool init(IItemInventory* item);
		bool loadBackground();
	private:
		std::string _qualityBGPath = "Background/";
		CC_SYNTHESIZE(IItemInventory*, _item, Item);
		Sprite* _icon;
		Label* _price;
	};
}

#endif // !__ITEM_SHOP_SLOT_H__
