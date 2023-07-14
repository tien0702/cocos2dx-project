#ifndef __DETAIL_ITEM_H__
#define __DETAIL_ITEM_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Inventory/Item/IItemInventory.h"
#include "UI/CoinBar.h"

USING_NS_CC;

namespace MyGame
{
	class DetailItem : public Sprite
	{
	public:
		static DetailItem* create(std::string backgroundPath);
		void renderItem(IItemInventory* item);
	protected:
		virtual bool init(std::string backgroundPath);
		virtual bool loadComponent();
		virtual bool loadPosition();
		virtual bool canAddItem();
		virtual bool canMinusItem();
		virtual void buy();
	protected:
		IItemInventory* _item;
		TTFConfig _font;
		int _currentNum = 1;
		Label* _itemName, * _itemDescription, * _itemNum, * _totalPrice;
		ui::Button* _paymentBtn, * _addBtn, * _minusBtn;
		CC_SYNTHESIZE(CoinBar*, _goldBar, GoldBar);
		
	};
}

#endif // !__DETAIL_ITEM_H__
