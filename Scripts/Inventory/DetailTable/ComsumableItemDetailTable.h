#ifndef __CONSUMABLE_DETIAL_TABLE_H__
#define __CONSUMABLE_DETIAL_TABLE_H__

#include "Inventory/DetailTable/DetailTable.h"
#include "ConsumableItem/ConsumableItem.h"
#include "ui/CocosGUI.h"

namespace MyGame
{
	class ConsumableDetailTable : public DetailTable
	{
	public:
		virtual bool init();
		CREATE_FUNC(ConsumableDetailTable);
		virtual void showItem(SlotBox* slotBox);
	protected:
		ui::Button* _useBT;
		ConsumableItem* _consumItem;
	};
}

#endif // !__CONSUMABLE_DETIAL_TABLE_H__
