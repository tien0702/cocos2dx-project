#ifndef __SHOP_CONTAINER_H__
#define __SHOP_CONTAINER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Shop/ContainerScrollView.h"
#include "Shop/BoxContainer.h"
#include "Shop/RowItem.h"
#include "Inventory/Item/IItemInventory.h"
#include "Shop/ItemShopSlot.h"
#include "Shop/DetailItem.h"

USING_NS_CC;

namespace MyGame
{
	class ShopContainer : public Node
	{
	public:
		static ShopContainer* create(std::string backgroundPath, std::vector<IItemInventory*> items, int maxColumn, DetailItem* detailItem);

	protected:
		virtual bool init(std::string backgroundPath, std::vector<IItemInventory*> items, int maxColumn, DetailItem* detailItem);
		virtual bool loadComponent();

		std::vector<RowItem*> getRowItems(std::vector<MyGame::IItemInventory*> items, int maxItems);
		void selectItemSlot(ItemShopSlot* itemSlot);

		bool loadSlots();
		bool loadContainer();
	protected:
		CC_SYNTHESIZE(int, _maxItems, MaxItems);
		ContainerScrollView* _boxScrollview;
		DetailItem* _detailItem;
		ItemShopSlot* _selectedItemSlot;
		Sprite* _selectedBorder;
		std::vector<ItemShopSlot*> _slots;
		std::vector<MyGame::IItemInventory*> _items;
	};
}

#endif // !__SHOP_CONTAINER_H__
