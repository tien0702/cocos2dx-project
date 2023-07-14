#ifndef __SLOT_BOX_H__
#define __SLOT_BOX_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Inventory/Item/IItemInventory.h"

USING_NS_CC;

namespace MyGame
{
	class SlotBox : public ui::Button
	{
	public:
		virtual bool init();
		SlotBox(IItemInventory* item);
		void refresh();
	protected:
		virtual void update(float dt);
		virtual bool loadProperties();
		virtual void loadBackground(ItemQuality quality);
		std::string _qualityBGPath = "Background/";
		CC_SYNTHESIZE(IItemInventory*, _item, InvItem);

		Label* _itemInfo;
		TTFConfig _font;
	};
}

#endif // !__SLOT_BOX_H__
