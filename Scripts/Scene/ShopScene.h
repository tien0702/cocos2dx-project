#ifndef __SHOP_SCENE_H__
#define __SHOP_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Shop/ContainerScrollView.h"
#include "Shop/BoxContainer.h"
#include "Shop/RowItem.h"
#include "Inventory/Item/IItemInventory.h"
#include "Shop/ItemShopSlot.h"
#include "Shop/DetailItem.h"
#include "UI/CoinBar.h"

USING_NS_CC;

namespace MyGame
{
	class ShopScene : public Scene
	{
	public:
		CREATE_FUNC(ShopScene);
	private:
		bool init();
		std::vector<IItemInventory*> getConsumItems();
		bool loadGoldBar();
		bool loadComponent();
	private:
		CoinBar* _goldBar;
		ui::Button* _backBtn;
	};
}

#endif // !__SHOP_SCENE_H__
