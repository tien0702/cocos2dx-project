#ifndef __DETAIL_TABLE__
#define __DETAIL_TABLE__

#include "Inventory/Item/IItemInventory.h"
#include "GameConfig.h"

namespace MyGame
{
	class SlotBox;
	class DetailTable : public Layer
	{
	public:
		virtual bool init();
		CREATE_FUNC(DetailTable);
		virtual void showItem(SlotBox* slotBox);
		Sprite* getBackground() { return _background; }
	protected:
		CC_SYNTHESIZE(std::string, _bgPath, BGPath);
		IItemInventory* _item;
		SlotBox* _slotBox;
		TTFConfig _font;
		Sprite* _background;
		Sprite* _header;
		Label* _itemName;
		Label* _itemDescription;
	protected:
		Color3B getColor(ItemQuality quality);
	};
}

#endif // !__DETAIL_TABLE__
